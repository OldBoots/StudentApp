
#ifndef DIALOG_H
#define DIALOG_H

#include "createdialog.h"
#include "trainingformdialog.h"
#include <QMessageBox>
#include <QDialog>
#include <QFile>



QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog

{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void slot_create();
    void slot_open();
    void slot_continue();
signals:
    void sign_show_training_form();
private:
    QString load_style(QString path);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
