
#ifndef DIALOG_H
#define DIALOG_H

#include "createdialog.h"
#include "trainingform.h"
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
signals:
    void sign_cend_list(QList <int>);
private:
    QString load_style(QString path);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
