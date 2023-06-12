#include "createdialog.h"
#include "ui_createdialog.h"

CreateDialog::CreateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Drawer);
    // Получчаем список дочерних layout из окна
    layout_list = ui->verticalLayout->findChildren<QHBoxLayout*>();
    QPushButton *butt;
    QSpinBox *spin_box;
    resource_path = "C:/Qt/project/StudentApp/SrcTrainingForm/";
    // Проходимся по всем дочерним элементам из списка layout
    for(int i = 0; i < layout_list.size(); ++i){
        if(layout_list[i]->objectName().left(7) == "hlayout"){
            // Получаем кнопку минус
            butt = qobject_cast<QPushButton*>(layout_list[i]->itemAt(2)->widget());
            // Задаем ей размер
            butt->setFixedSize(16,16);
            // Рисуем в ней знак минус
            butt->setIcon(QPixmap(":/minus.png").scaled(8,8));
            // Применяем CSS код из файла
            butt->setStyleSheet(read_file(":/StyleButtPlasMinus.css"));
            // Соединяем нажатие кнопки со слотом
            connect(butt, SIGNAL(clicked()), SLOT(slot_minus()));
            // Получаем спин бокс
            spin_box = qobject_cast<QSpinBox*>(layout_list[i]->itemAt(3)->widget());
            // Задаем размер
            spin_box->setFixedSize(30, 20);
            // Убираем вертикальные кнопки
            spin_box->setButtonSymbols(QAbstractSpinBox::NoButtons);

            butt = qobject_cast<QPushButton*>(layout_list[i]->itemAt(4)->widget());
            butt->setFixedSize(16,16);
            butt->setIcon(QPixmap(":/plus.png").scaled(8,8));
            butt->setStyleSheet(read_file(":/StyleButtPlasMinus.css"));
            connect(butt, SIGNAL(clicked()), SLOT(slot_plus()));
        }else{
            layout_list.remove(i);
        }
    }

//    load_url();

    connect(ui->butt_cancel, SIGNAL(clicked()), SLOT(reject()));
    connect(ui->butt_create, SIGNAL(clicked()), SLOT(slot_create_form()));
    connect(&web_page, SIGNAL(loadFinished(bool)), SLOT(slot_parse_tasks()));
//    connect(&temp_page, SIGNAL(loadFinished(bool)), SLOT(slot_load_page()));
    connect(this, SIGNAL(sign_task_processing_completed()), SLOT(slot_task_processing()));
    connect(this, SIGNAL(sign_task_parsing_completed()), SLOT(slot_show_web_page()));
    connect(&timer_waiting, SIGNAL(timeout()), SLOT(slot_waiting_overrun()));
    connect(this, SIGNAL(sign_stage_change(int)), &progress_bar, SLOT(setValue(int)));
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

void CreateDialog::remove_last_try()
{
    QFile file;
    file.setFileName(resource_path + "ProgNumber");
    file.remove();
    file.setFileName(resource_path + "ProgTable");
    file.remove();
    file.setFileName(resource_path + "ProgString");
    file.remove();
    file.setFileName(resource_path + "ProgCheckbox");
    file.remove();
    file.setFileName(resource_path + "html.html");
    file.remove();
}

void CreateDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    this->reject();
}

void CreateDialog::slot_create_form()
{
    cur_num = 0;
    num_quest = 0;
    body_html.clear();
    flag_overrun = false;
    remove_last_try();
    stage = 0;
    progress_bar.setRange(0, 100);
    ui->verticalLayout->addWidget(&progress_bar);
    emit sign_task_processing_completed();
}

void CreateDialog::slot_waiting_overrun()
{
    flag_overrun = true;
    QMessageBox m_box(QMessageBox::Warning, tr("Ошибка"), tr("Не удалось загрузить задания."));
    m_box.setWindowFlags(Qt::SubWindow);
    m_box.setInformativeText("Попробуйте использовать локальную базу данных.");
    m_box.exec();
    timer_waiting.stop();
}

//void CreateDialog::slot_load_page()
//{
//    QString buf;
//    temp_page.page()->runJavaScript("document.body.innerHTML", [&]
//                                   (QVariant result) {
//                                       buf = result.toString();
//                                   });
//    while(buf.isEmpty() && !flag_overrun){
//        QApplication::processEvents();
//    }
//    QFile file(resource_path + "FullPage.html");
//    QTextStream stream(&file);
//    file.open(QIODevice::WriteOnly);
//    stream << buf;
//    file.close();
//}

void CreateDialog::slot_task_processing()
{
    QSpinBox *spin_box;
    int value;
    spin_box = qobject_cast<QSpinBox*>(layout_list[cur_num]->itemAt(3)->widget());
    value = spin_box->value();
    emit sign_stage_change(qCeil((100.0 / 6.0) * (double)(++stage)));
    if(value != 0){
        count_quest = value;
        if(ui->check_box_lockal_base->isChecked()){
            web_page.load(QUrl::fromLocalFile(resource_path + "test" + QString::number(cur_num) + ".html"));
        } else{
            QMessageBox m_box(QMessageBox::Warning, tr("Предупреждение"), tr("Данная функция пока не реализована."));
            m_box.setWindowFlags(Qt::SubWindow);
            m_box.setInformativeText("Попробуйте использовать локальную базу данных.");
            m_box.exec();
//            temp_page.load(QUrl(list_url[cur_num]));
        }
        timer_waiting.start(8000);
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
    QString temp_str;
    temp_str = read_file(resource_path + "ReadTask" + QString::number(cur_num) + ".js");
    temp_str = set_JS_data(temp_str, "count", QString::number(count_quest));
    temp_str = set_JS_data(temp_str, "num_quest", QString::number(num_quest));
    web_page.page()->runJavaScript(temp_str, [&]
                                   (QVariant result) {
                                       buf = result.toString();
                                       if(buf.size() < 10){
                                           buf.clear();
                                       }
                                   });
    timer_waiting.start(8000);
    while(buf.isEmpty() && !flag_overrun){
        QApplication::processEvents();
    }
    timer_waiting.stop();
    num_quest += count_quest;
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
    QFile file(resource_path + "html.html");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);
    stream << "<html>"
           << "<body>" << "<link rel=\"stylesheet\" href=\""+ resource_path +"/MyStyle.css\">" << body_html << "</body>"
           << "</html>";
    file.close();
    accept();
}



CreateDialog::~CreateDialog()
{
    delete ui;
}

QString CreateDialog::read_file(QString path)
{
    QString str;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

//void CreateDialog::load_url()
//{
//    QString str_url;
//    QFile file(":/Url.txt");
//    file.open(QIODevice::ReadOnly);
//    str_url = file.readAll();
//    list_url = str_url.split("\r\n");
//    file.close();
//}

void CreateDialog::replace_value_in_str(QString &str, QString value_name, QString value){
    int index;
    QString temp_str = "~" + value_name + "~";
    index = str.indexOf(temp_str);
    str = str.left(index) + value + str.right(str.size() - (index + temp_str.size()));
}

QString CreateDialog::set_JS_data(QString file_str, QString value_name, QString value)
{
    QString str = file_str;
    replace_value_in_str(str, value_name, value);
    return str;
}
