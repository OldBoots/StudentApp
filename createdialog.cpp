#include "createdialog.h"
#include "ui_createdialog.h"

CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog)
{
    ui->setupUi(this);
    layout_list = ui->verticalLayout->findChildren<QHBoxLayout*>();
    QPushButton *butt;
    QSpinBox *spin_box;
    for(int i = 0; i < layout_list.size(); ++i){
        if(layout_list[i]->objectName().left(7) == "hlayout"){
            butt = qobject_cast<QPushButton*>(layout_list[i]->itemAt(2)->widget());
            butt->setFixedSize(16,16);
            butt->setIcon(QPixmap(":/minus.png").scaled(8,8));
            butt->setStyleSheet(load_file(":/StyleButtPlasMinus.css"));
            connect(butt, SIGNAL(clicked()), SLOT(slot_minus()));

            spin_box = qobject_cast<QSpinBox*>(layout_list[i]->itemAt(3)->widget());
            spin_box->setFixedSize(30, 20);
            spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);

            butt = qobject_cast<QPushButton*>(layout_list[i]->itemAt(4)->widget());
            butt->setFixedSize(16,16);
            butt->setIcon(QPixmap(":/plus.png").scaled(8,8));
            butt->setStyleSheet(load_file(":/StyleButtPlasMinus.css"));
            connect(butt, SIGNAL(clicked()), SLOT(slot_plus()));
        }else{
            layout_list.remove(i);
        }
    }

    load_url();

    ui->verticalLayout->addWidget(&web_page);

    connect(ui->butt_cancel, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->butt_create, SIGNAL(clicked()), SLOT(slot_create_form()));
    connect(&web_page, SIGNAL(loadFinished(bool)), SLOT(slot_parse_tasks()));
    connect(this, SIGNAL(sign_task_processing_completed()), SLOT(slot_task_processing()));
    connect(this, SIGNAL(sign_task_parsing_completed()), SLOT(slot_show_web_page()));
    connect(&timer_waiting, SIGNAL(timeout()), SLOT(slot_waiting_overrun()));
}

void CreateDialog::slot_plus(){
    QPushButton* butt = qobject_cast<QPushButton*>(sender());
    int value;
    if (butt != 0){
        QSpinBox *spin_box = qobject_cast<QSpinBox*>(layout_list[butt->objectName().right(1).toInt()]->itemAt(3)->widget());
        value = spin_box->value();
        if(value < 10){
            spin_box->setValue(++value);
        }
    } else{
        Q_ASSERT(butt != 0);
    }
}

void CreateDialog::slot_minus(){
    QPushButton* butt = qobject_cast<QPushButton*>(sender());
    int value;
    if (butt != 0){
        QSpinBox *spin_box = qobject_cast<QSpinBox*>(layout_list[butt->objectName().right(1).toInt()]->itemAt(3)->widget());
        value = spin_box->value();
        if(value > 0){
            spin_box->setValue(--value);
        }
    } else{
        Q_ASSERT(butt != 0);
    }
}

void CreateDialog::slot_create_form()
{
    cur_num = 0;
    num_quest = 0;
    flag_overrun = false;
    ui->label_status->clear();
    emit sign_task_processing_completed();
}

void CreateDialog::slot_waiting_overrun()
{
    flag_overrun = true;
//    qDebug("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    ui->label_status->setText("Не удалось загрузить задания.\nПопробуйте использовать локальную базу данных.");
    timer_waiting.stop();
}

void CreateDialog::slot_task_processing()
{
    QSpinBox *spin_box;
    int value;
    spin_box = qobject_cast<QSpinBox*>(layout_list[cur_num]->itemAt(3)->widget());
    value = spin_box->value();
    if(value != 0){
        count_quest = value;
        current_type = spin_box->objectName().right(1).toInt();
        if(ui->check_box_lockal_base->isChecked()){
            web_page.load(QUrl::fromLocalFile("C:/Qt/Project/StudentApp/test" + QString::number(current_type) + ".html"));
        } else{
//            web_page.load(QUrl(list_url[current_type]));
        }
        timer_waiting.start(5000);
    }else{
        ++cur_num;
        if(cur_num < layout_list.size()){
            emit sign_task_processing_completed();
        } else{
            emit sign_task_parsing_completed();
        }
    }
}

void CreateDialog::slot_parse_tasks()
{
    timer_waiting.stop();
    QString buf;
    web_page.page()->runJavaScript(set_JS_data(":/ReadTask" + QString::number(current_type)), [&]
                                   (QVariant result) {
                                       buf = result.toString();
                                   });
    timer_waiting.start(5000);
    while(buf.isEmpty() && !flag_overrun){
        QApplication::processEvents();
    }
    timer_waiting.stop();
    if(flag_overrun){
        return;
    }
    body_html += buf;
    ++cur_num;
    if(cur_num < layout_list.size()){
        emit sign_task_processing_completed();
    } else{
        emit sign_task_parsing_completed();
    }
}

void CreateDialog::slot_show_web_page()
{
    QFile file("C:/Qt/Project/StudentApp/html.html");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);
    stream << "<html>" << "<body>" << "<link rel=\"stylesheet\" href=\"qrc:/MyStyle.css\">" << body_html << "</body>" << "</html>";
    file.close();
    web_page.load(QUrl::fromLocalFile(file.fileName()));
}



CreateDialog::~CreateDialog()
{
    delete ui;
}

QString CreateDialog::load_file(QString path)
{
    QString str;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

void CreateDialog::load_url()
{
    QString str_url;
    QFile file(":/Url.txt");
    file.open(QIODevice::ReadOnly);
    str_url = file.readAll();
    list_url = str_url.split("\r\n");
    file.close();
}

QString CreateDialog::set_JS_data(QString file_path)
{
    QString str_file;
    int index;
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);
    str_file = file.readAll();
    file.close();
    index = str_file.indexOf("~count~");
    str_file = str_file.left(index) + QString::number(count_quest) + str_file.right(str_file.size() - (index + 7));
    index = str_file.indexOf("~quest~");
    str_file = str_file.left(index) + QString::number(num_quest) + str_file.right(str_file.size() - (index + 7));
    num_quest += count_quest;
    return str_file;
}
