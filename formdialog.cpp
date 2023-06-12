#include "formdialog.h"
#include "ui_formdialog.h"

FormDialog::FormDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormDialog)
{
    ui->setupUi(this);
    this->setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    form_src = "C:/Qt/project/StudentApp/SrcForm/";
    ui->scrollArea->setFixedSize(200, 300);
    ui->horizontalLayout->addWidget(&web_view);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    flag_end_try = false;
    load_form();
    connect(&web_view, SIGNAL(loadFinished(bool)), SLOT(slot_finished_form_load()));
    connect(ui->butt_end_try, SIGNAL(clicked(bool)), SLOT(slot_end_try()));
    connect(ui->butt_close, SIGNAL(clicked(bool)), SLOT(slot_close()));
    connect(ui->listView, SIGNAL(clicked(QModelIndex)), SLOT(slot_scroll_to_task(QModelIndex)));
}

void FormDialog::load_form()
{
    web_view.load(form_src + "Form.html");
}

void FormDialog::save_progress()
{
    QString prog_data;
    prog_data = run_JS_str_gd(web_view, "save_progress()").toString();
    qDebug() << prog_data;
    QFile file(form_src + "ProgFile");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);
    stream << prog_data;
    file.close();
}

void FormDialog::load_progress()
{
    qDebug("load");
    QString temp_str;
    QStringList temp_list, temp_value;
    QString str_input_value;
    QString str_text_value;
    QString str_checkbox_state;
    QFile file(form_src + "ProgFile");
    file.open(QIODevice::ReadOnly);
    temp_str = file.readAll();
    file.close();
    temp_list = temp_str.split("~");
    for(int i = 0; i < temp_list.size(); i++){
        temp_value = temp_list[i].split("=");
        if(temp_value[0] == "i"){
            str_input_value += temp_value[1] + "~";
        }else if(temp_value[0] == "t"){
            str_text_value += temp_value[1] + "~";
        }else if(temp_value[0] == "c"){
            str_checkbox_state += temp_value[1] + "~";
        }
    }
    if(!str_input_value.isEmpty()){
        run_JS_str_wr(web_view, "load_input_prog(\"" + str_input_value + "\")", false);
    }
    if(!str_text_value.isEmpty()){
        run_JS_str_wr(web_view, "load_textarea_prog(\"" + str_text_value + "\")", false);
    }
    if(!str_checkbox_state.isEmpty()){
        run_JS_str_wr(web_view, "load_checkbox_prog(\"" + str_checkbox_state + "\")", false);
    }
}

void FormDialog::slot_scroll_to_task(QModelIndex index)
{
    QStringList temp_list = model.data(index).toString().split(" ");
    run_JS_str_wr(web_view, "document.getElementById(\"task_number_id_" + temp_list[temp_list.size() - 1] + "\").scrollIntoView();", false);
}

void FormDialog::slot_finished_form_load()
{
    if(QFileInfo::exists(form_src + "ProgFile")){
        load_progress();
    }
    show_task_list();
}

void FormDialog::slot_end_try()
{
    int type_task;
    for(int i = 0; i < list_task_num.size(); i++){
        type_task = run_JS_str_gd(web_view, "get_type(\"" + QString::number(i) + "\")").toInt();
        qDebug() << "num" << i + 1 << "type =" << run_JS_str_gd(web_view, "get_type(\"" + QString::number(i) + "\")").toString();
        switch (type_task) {
        case 1:
            result << run_JS_str_gd(web_view, "check_string_num_task(\"" + QString::number(i) + "\")").toInt();
            break;
        case 2:
            result << run_JS_str_gd(web_view, "check_string_num_task(\"" + QString::number(i) + "\")").toInt();
            break;
        case 3:
            result << run_JS_str_gd(web_view, "check_comp_task(\"" + QString::number(i) + "\")").toInt();
            break;
        case 4:
            result << run_JS_str_gd(web_view, "check_string_num_task(\"" + QString::number(i) + "\")").toInt();
            break;
        case 5:
            result << run_JS_str_gd(web_view, "check_table_string_task(\"" + QString::number(i) + "\")").toInt();
            break;
        case 6:
            result << run_JS_str_gd(web_view, "check_multi_task(\"" + QString::number(i) + "\")").toInt();
            break;
        case 7:
            result << run_JS_str_gd(web_view, "check_28line_task(\"" + QString::number(i) + "\")").toInt();
            break;
        }
        qDebug() << result[i];
    }
    flag_end_try = true;
    show_result();
    ui->butt_end_try->setEnabled(false);
    run_JS_str_wr(web_view, "disable_form()", false);
    run_JS_str_wr(web_view, "show_solution()", false);
}

void FormDialog::closeEvent (QCloseEvent *event)
{
    Q_UNUSED(event);
    slot_close();
}

void FormDialog::slot_close()
{
    if(!flag_end_try){
        CloseDialog dialog(this);
        if(!dialog.exec()){
            return;
        }
        flag_end_try = dialog.get_flag();
    }
    if(flag_end_try){
        QFile file;
        file.setFileName(form_src + "Form.html");
        file.remove();
        file.setFileName(form_src + "ProgFile");
        file.remove();
    }else{
        save_progress();
    }
    this->accept();
}

FormDialog::~FormDialog()
{
    delete ui;
}

void FormDialog::show_task_list()
{
    int count_task = run_JS_str_gd(web_view, "document.getElementsByClassName(\"maindiv\").length").toInt();
    qDebug() << count_task;
    for(int i = 0; i < count_task; i++){
        list_task_num << "Задание номер " + QString::number(i + 1);
                                                model.appendRow(new QStandardItem(list_task_num[i]));
    }
    ui->listView->setModel(&model);
}

void FormDialog::show_result(){
    int temp_result;
    for(int i = 0; i < result.size(); i++){
        QModelIndex index_model_data;
        QColor result_color;
        temp_result = result[i];
        index_model_data = model.index(i, 0);
        if(temp_result == 0 && temp_result <= 25){
            result_color.setRgb(255, 0, 0);
        }else if(temp_result > 25 && temp_result <= 50){
            result_color.setRgb(250, 115, 0);
        }else if(temp_result > 50 && temp_result <= 70){
            result_color.setRgb(154, 205, 50);
        }else if(temp_result > 70 && temp_result <= 100){
            result_color.setRgb(100, 255, 50);
        }
        model.setData(index_model_data, QString::number(temp_result) + "% " + list_task_num[i]);
        model.setData(index_model_data, QBrush(result_color), Qt::ForegroundRole);
    }
}

bool FormDialog::run_JS_str_wr(QWebEngineView &web, QString js_str, int w_flg)
{
    bool ok = false;
    web.page()->runJavaScript(js_str, [&](QVariant result){
        if(w_flg){
            ok = result.toBool();
            qDebug() << ok;
        }else{
            ok = true;
        }
    });
    while(!ok){
        QApplication::processEvents();
    }
    return ok;
}

QVariant FormDialog::run_JS_str_gd(QWebEngineView &web, QString js_str)
{
    QVariant data;
    web.page()->runJavaScript(js_str, [&](QVariant result){
        data = result;
    });
    while(data.isNull()){
        QApplication::processEvents();
    }
    return data;
}

QString FormDialog::read_file(QString path)
{
    QString str;
    QFile file(form_src + path);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

void FormDialog::replace_value_in_str(QString &str, QString value_name, QString value){
    int index;
    QString temp_str = "~" + value_name + "~";
    index = str.indexOf(temp_str);
    str = str.left(index) + value + str.right(str.size() - (index + temp_str.size()));
}

QString FormDialog::set_JS_data(QString file_str, QString value_name, QString value)
{
    QString str = file_str;
    replace_value_in_str(str, value_name, value);
    return str;
}
