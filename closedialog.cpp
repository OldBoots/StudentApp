#include "closedialog.h"
#include "ui_closedialog.h"

CloseDialog::CloseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CloseDialog)
{
    ui->setupUi(this);
    flag_end_try = false;
    this->setWindowFlags(Qt::Tool);
    this->setWindowTitle("Предупреждение");
    connect(ui->butt_close, SIGNAL(clicked(bool)), SLOT(accept()));
    connect(ui->butt_cancel, SIGNAL(clicked(bool)), SLOT(reject()));
    connect(ui->butt_end_close, SIGNAL(clicked(bool)), SLOT(slot_end_close()));
}

CloseDialog::~CloseDialog()
{
    delete ui;
}

void CloseDialog::slot_end_close()
{
    flag_end_try = true;
    accept();
}

bool CloseDialog::get_flag()
{
    return flag_end_try;
}
