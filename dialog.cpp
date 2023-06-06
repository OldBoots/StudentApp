
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background:transparent;");
    ui->frame->setStyleSheet(load_style(":/StyleWindow.css"));

    resource_path = "C:/Qt/project/StudentApp/";

    ui->butt_create->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_open->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_close->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_continue->setStyleSheet(load_style(":/StyleButtMenu.css"));

    connect(ui->butt_close, SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->butt_create, SIGNAL(clicked(bool)), SLOT(slot_create()));
    connect(ui->butt_continue, SIGNAL(clicked(bool)), SLOT(slot_continue()));
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slot_create()
{
    CreateDialog create_dialog;
    if(create_dialog.exec()){
        TrainingFormDialog training_form;
        this->hide();
        if(training_form.exec()){
            this->show();
        }else{
            this->close();
        }
    }
}

void Dialog::slot_open()
{

}

void Dialog::slot_continue()
{
    if(QFileInfo::exists(resource_path + "html.html")){
        TrainingFormDialog training_form;
//        this->hide();
        if(!training_form.exec()){
            QMessageBox m_box;
            //        m_box.setWindowIcon();
            m_box.setWindowTitle("Предупреждение");
            m_box.setText("Форма не была открыта. Возможно тренировочный бланк удален, или поврежден. ");
            m_box.setInformativeText("Создайте новый тренировочный бланк");
            m_box.setDefaultButton(QMessageBox::Ok);
            m_box.exec();
        }
//        this->show();
    }else{
        QMessageBox m_box;
//        m_box.setWindowIcon();
        m_box.setWindowTitle("Предупреждение");
        m_box.setText("Тренировочный бланк отсутствует.");
        m_box.setInformativeText("Создайте тренировойчный бланк.");
        m_box.setDefaultButton(QMessageBox::Ok);
        m_box.exec();
//        this->show();
    }
}

QString Dialog::load_style(QString path)
{
    QString str;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

