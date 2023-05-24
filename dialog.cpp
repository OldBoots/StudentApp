
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

    connect(ui->butt_close, SIGNAL(clicked()), SLOT(close()));
    connect(ui->butt_create, SIGNAL(clicked()), SLOT(slot_create()));
    connect(this, SIGNAL(sign_show_training_form()), &training_form, SLOT(slot_show_form()));
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::slot_create()
{
    CreateDialog create_dialog;
    if(create_dialog.exec()){
        qDebug("pizza");
        emit sign_show_training_form();
        this->hide();
    }
}

void Dialog::slot_open()
{

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

