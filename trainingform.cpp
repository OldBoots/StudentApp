#include "trainingform.h"
#include "ui_trainingform.h"

TrainingForm::TrainingForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrainingForm)
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(&web_view);
    resource_path = "C:/Qt/Project/StudentApp/";
    connect(&web_view, SIGNAL(loadFinished(bool)), SLOT(slot_count_ex()));
    connect(ui->butt_end_try, SIGNAL(clicked(bool)), SLOT(slot_end_try()));
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

void TrainingForm::slot_count_ex()
{
    int count = 0;
    web_view.page()->runJavaScript(read_file(":/ReadCountTasks"), [&]
                                   (QVariant result)->void {
                                       count = result.toInt();
        qDebug() << count;
                                   });
    while(count == 0){
        QApplication::processEvents();
    }
    for(int i = 0; i < count; i++){
        list_task_number.push_back("Задание номер " + QString::number(i + 1));
    }
    string_model.setStringList(list_task_number);
    ui->listView->setModel(&string_model);
}

void TrainingForm::slot_end_try()
{
    QString buf;
    for(int i = 0; i < list_task_number.size(); i++){
        buf.clear();
        web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + "GetTaskType.js"), "index_task", QString::number(i)), [&]
                                       (QVariant result) {
                                           buf = result.toString();
                                       });
        while(buf.isEmpty()){
            QApplication::processEvents();
        }
        if(buf == "string"){
            buf.clear();
            web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + "CheckStringSolution.js"), "index_task", QString::number(i)), [&]
                                           (QVariant result) {
                                               buf = result.toString();
                                           });
            while(buf.isEmpty()){
                QApplication::processEvents();
            }
            if(buf == "true"){
                qDebug() << buf;
            } else{
                qDebug() << buf;
            }
        }
        if(buf == "number"){
            buf.clear();
            web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + "CheckNumberSolution.js"), "index_task", QString::number(i)), [&]
                                      (QVariant result) {
                                          buf = result.toString();
                                      });
            while(buf.isEmpty()){
                QApplication::processEvents();
            }
            if(buf == "true"){
                qDebug() << buf;
            } else{
                qDebug() << buf;
            }
        }
        if(buf == "numberimg"){
            buf.clear();
            web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + "CheckNumberImgSolution.js"), "index_task", QString::number(i)), [&]
                                      (QVariant result) {
                                          buf = result.toString();
                                      });
            while(buf.isEmpty()){
                QApplication::processEvents();
            }
            if(buf == "true"){
                qDebug() << buf;
            } else{
                qDebug() << buf;
            }
        }
        if(buf == "numbertable"){
            buf.clear();
            web_view.page()->runJavaScript(set_JS_data(read_file(resource_path + "CheckNumberTableSolution.js"), "index_task", QString::number(i)), [&]
                                      (QVariant result) {
                                          buf = result.toString();
                                      });
            while(buf.isEmpty()){
                QApplication::processEvents();
            }
            if(buf == "true"){
                qDebug() << buf;
            } else{
                qDebug() << buf;
            }
        }
    }
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
//    qDebug("__________________________________________________________________");
//    qDebug() << str;
    return str;
}
