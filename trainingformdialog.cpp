#include "trainingformdialog.h"
#include "ui_trainingformdialog.h"

TrainingFormDialog::TrainingFormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrainingFormDialog)
{
    ui->setupUi(this);
    ui->scrollArea->setFixedSize(200, 300);
    ui->horizontalLayout->addWidget(&web_view);
    resource_path = "C:/Qt/project/StudentApp/";
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flag_end_try = false;
    open_form();
    connect(&web_view, SIGNAL(loadFinished(bool)), SLOT(slot_finish_load_form()));
    connect(ui->butt_end_try, SIGNAL(clicked(bool)), SLOT(slot_end_try()));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), SLOT(slot_go_to_task(QModelIndex)));
    connect(ui->butt_close, SIGNAL(clicked(bool)), SLOT(slot_close()));
    this->setWindowFlags(Qt::Window);
}

void TrainingFormDialog::closeEvent (QCloseEvent *event)
{
    Q_UNUSED(event);
    slot_close();
}

void TrainingFormDialog::open_form()
{
        web_view.page()->load(QUrl::fromLocalFile(resource_path + "html.html"));
}

void TrainingFormDialog::save_progress(QString field_type, QString file_name)
{
    QString temp_str = "~~";
    QFile file(resource_path + file_name);
    QTextStream stream(&file);
//    qDebug() << file_name;
    web_view.page()->runJavaScript(set_JS_data(read_file("SaveProgTasks.js"), "field_type", field_type), [&]
                                   (QVariant result) {
                                       temp_str = result.toString();
//                                       qDebug() << temp_str;
                                   });
    while(temp_str == "~~"){
//        qDebug() << temp_str;
        QApplication::processEvents();
    }
    if(temp_str != "-1"){
        file.open(QIODevice::WriteOnly);
        stream << temp_str;
        file.close();
    }
    temp_str.clear();
}

void TrainingFormDialog::load_progress(QString field_type, QString file_name)
{
    if(QFileInfo::exists(resource_path + file_name)){
        QString str, temp_js_str, ok;
        QFile file(resource_path + file_name);
        file.open(QIODevice::ReadOnly);
        str = file.readAll();
        file.close();
        if(!str.isEmpty()){
            temp_js_str = read_file("LoadProgTasks.js");
            temp_js_str = set_JS_data(temp_js_str, "field_type", field_type);
            temp_js_str = set_JS_data(temp_js_str, "str", str);
            web_view.page()->runJavaScript(temp_js_str, [&]
                                           (QVariant result) {
                                               ok = result.toString();
                                               qDebug() << ok;
                                           });
            while(ok.isEmpty()){
                QApplication::processEvents();
            }
        }
        file.remove();
    }
}

TrainingFormDialog::~TrainingFormDialog()
{
    delete ui;
}

void TrainingFormDialog::slot_finish_load_form()
{
    show_number_task();
    load_progress("number", "ProgNumber");
    load_progress("table", "ProgTable");
    load_progress("string", "ProgString");
    load_progress("checkbox", "ProgCheckbox");
}

void TrainingFormDialog::slot_end_try()
{
    QString buf;
    int result;
    for(int i = 0; i < string_model.rowCount(); i++){
        buf.clear();
        web_view.page()->runJavaScript(set_JS_data(read_file("GetTaskType.js"), "index_task", QString::number(i)), [&]
                                       (QVariant result) {
                                           buf = result.toString();
                                       });
        while(buf.isEmpty()){
            QApplication::processEvents();
        }
        if(buf == "string"){
            result = check_task_answer("CheckStringSolution.js", i);
        } else if(buf == "number" || buf == "sequence"){
            result = check_task_answer("CheckNumberSolution.js", i);
        } else if(buf == "numberimg"){
            result = check_task_answer("CheckNumberImgSolution.js", i);
        } else if(buf == "numbertable"){
            result = check_task_answer("CheckNumberTableSolution.js", i);
        } else if(buf == "multianswer"){
            result = check_task_answer("CheckMultiAnswerSolution.js", i);
        } else{
            QMessageBox::warning(this, tr("Ошибка"),
                                           tr("Не получается определить тип задания."));
        }
        buf.clear();
        show_results(result, i);
    }
    flag_end_try = true;
    web_view.page()->runJavaScript(read_file("DisableForm.js"));
    web_view.page()->runJavaScript(read_file("ShowSolution.js"));
    ui->butt_end_try->setEnabled(false);
}

void TrainingFormDialog::slot_close()
{
    if(!flag_end_try){
        CloseDialog dialog(this);
        if(!dialog.exec()){
            return;
        }
        flag_end_try = dialog.get_flag();
    }
    if(flag_end_try){
        QFile file(resource_path + "html.html");
        file.remove();
    }else{
        save_progress("number", "ProgNumber");
        save_progress("table", "ProgTable");
        save_progress("string", "ProgString");
        save_progress("checkbox", "ProgCheckbox");
    }
    this->accept();
}

void TrainingFormDialog::show_results(int result, int index)
{
    QModelIndex index_model_data = string_model.index(index, 0);
    string_model.setData(index_model_data, QString::number(qCeil(((double)100 / (double)3) * (double)result)) + "% " + list_task_number[index]);
    QColor result_color;
    switch (result) {
    case 0:
        result_color.setRgb(255, 0, 0);
        break;
    case 1:
        result_color.setRgb(250, 115, 0);
        break;
    case 2:
        result_color.setRgb(154, 205, 50);
        break;
    case 3:
        result_color.setRgb(100, 255, 50);
        break;
    default:
        break;
    }
    string_model.setData(index_model_data, QBrush(result_color), Qt::ForegroundRole);
}

void TrainingFormDialog::slot_go_to_task(QModelIndex data_index)
{
    QStringList temp_list = string_model.data(data_index).toString().split(" ");
    web_view.page()->runJavaScript("document.getElementById(\"nums_id" + temp_list[temp_list.size() - 1] + "\").scrollIntoView();");
}

void TrainingFormDialog::show_number_task()
{
    int count = 0;
    web_view.page()->runJavaScript("document.getElementsByClassName(\"prob_nums\").length", [&]
                                   (QVariant result)->void {
                                       count = result.toInt();
                                   });
    while(count == 0){
        QApplication::processEvents();
    }
    for(int i = 0; i < count; i++){
        list_task_number << "Задание номер " + QString::number(i + 1);
                                                   string_model.appendRow(new QStandardItem(list_task_number[i]));
    }
    ui->listView->setModel(&string_model);
}

int TrainingFormDialog::check_task_answer(QString file_nmae, int index)
{
    int result = -1;
    web_view.page()->runJavaScript(set_JS_data(read_file(file_nmae), "index_task", QString::number(index)), [&]
                                   (QVariant temp) {
                                       result = temp.toInt();
                                   });
    while(result == -1){
        QApplication::processEvents();
    }
    return result;
}

QString TrainingFormDialog::read_file(QString path)
{
    QString str;
    QFile file(resource_path + path);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

void TrainingFormDialog::replace_value_in_str(QString &str, QString value_name, QString value){
    int index;
    QString temp_str = "~" + value_name + "~";
    index = str.indexOf(temp_str);
    str = str.left(index) + value + str.right(str.size() - (index + temp_str.size()));
}

QString TrainingFormDialog::set_JS_data(QString file_str, QString value_name, QString value)
{
    QString str = file_str;
    replace_value_in_str(str, value_name, value);
    return str;
}
