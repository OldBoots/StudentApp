
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

    ui->butt_create->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_open->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_close->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_continue->setStyleSheet(load_style(":/StyleButtMenu.css"));

    connect(ui->butt_close, SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->butt_create, SIGNAL(clicked(bool)), SLOT(slot_create()));
    connect(ui->butt_continue, SIGNAL(clicked(bool)), SLOT(slot_continue()));
//    connect(this, SIGNAL(sign_show_training_form()), &training_form, SLOT(slot_show_form()));
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
            this->show();
            QMessageBox::warning(this, tr("Предупреждение"),
                                           tr("Тренировочный бланк отсутствует. Создайте тренировойчный бланк."));
        }
    }
}

void Dialog::slot_open()
{

}

void Dialog::slot_continue()
{
    TrainingFormDialog training_form;
    this->hide();
    if(training_form.exec()){
        this->show();
    }else{
        this->close();
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

