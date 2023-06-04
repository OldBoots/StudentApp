#include "trainingform.h"
#include "ui_trainingform.h"

TrainingForm::TrainingForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrainingForm)
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(&web_view);
    resource_path = "C:/Qt/Project/StudentApp/";
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flag_end_try = false;
    connect(&web_view, SIGNAL(loadFinished(bool)), SLOT(slot_show_number_task()));
    connect(ui->butt_end_try, SIGNAL(clicked(bool)), SLOT(slot_end_try()));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), SLOT(slot_go_to_task(QModelIndex)));
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

void TrainingForm::slot_show_form()
{
    web_view.page()->load(QUrl::fromLocalFile(resource_path + "html.html"));
    this->show();
    ui->scrollArea->setFixedSize(200, 300);
}

void TrainingForm::slot_show_number_task()
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

void TrainingForm::slot_end_try()
{
    QString buf;
    int result;
    for(int i = 0; i < string_model.rowCount(); i++){
        buf.clear();
        web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + "GetTaskType.js"), "index_task", QString::number(i)), [&]
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
        web_view.page()->runJavaScript(read_file(resource_path + "DisableForm.js"));
        ui->butt_end_try->setEnabled(false);
    }
}

void TrainingForm::slot_close()
{
    if(!flag_end_try){
        CloseDialog dialog(this);
        if(dialog.exec()){
            close();
        }
    }
}

void TrainingForm::show_results(int result, int index)
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

void TrainingForm::slot_go_to_task(QModelIndex data_index)
{
    QStringList temp_list = string_model.data(data_index).toString().split(" ");
    web_view.page()->runJavaScript("document.getElementById(\"nums_id" + temp_list[temp_list.size() - 1] + "\").scrollIntoView();");
}

int TrainingForm::check_task_answer(QString file_nmae, int index)
{
    int result = -1;
    web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + file_nmae), "index_task", QString::number(index)), [&]
                                   (QVariant temp) {
                                       result = temp.toInt();
                                   });
    while(result == -1){
        QApplication::processEvents();
    }
    return result;
}

QString TrainingForm::read_file(QString path)
{
    QString str;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

void TrainingForm::replace_value_in_str(QString &str, QString value_name, QString value){
    int index;
    QString temp_str = "~" + value_name + "~";
    index = str.indexOf(temp_str);
    str = str.left(index) + value + str.right(str.size() - (index + temp_str.size()));
}

QString TrainingForm::set_JS_data(QString file_str, QString value_name, QString value)
{
    QString str = file_str;
    replace_value_in_str(str, value_name, value);
    return str;
}
