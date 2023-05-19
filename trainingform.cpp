#include "trainingform.h"
#include "ui_trainingform.h"

TrainingForm::TrainingForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrainingForm)
{
    ui->setupUi(this);
    web_view;
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

void TrainingForm::slot_create_form(QList<int> list_tusk_number)
{
    qDebug() << list_tusk_number;
    show();
}
