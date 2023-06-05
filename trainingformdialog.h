#ifndef TRAININGFORMDIALOG_H
#define TRAININGFORMDIALOG_H

#include <QDialog>
#include <QWebEngineView>
#include <QUrl>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringListModel>
#include <QRegularExpression>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QFileInfo>
#include "closedialog.h"

namespace Ui {
class TrainingFormDialog;
}

class TrainingFormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingFormDialog(QWidget *parent = nullptr);
    ~TrainingFormDialog();
private slots:
//    void slot_show_form();
    void slot_show_number_task();
    void slot_end_try();
    void slot_close();
    void slot_go_to_task(QModelIndex);
private:
    QString read_file(QString path);
    QString set_JS_data(QString file_path, QString value_name, QString value);
    void replace_value_in_str(QString &str, QString value_name, QString value);
    void show_results(int result, int index_model_data);
    int check_task_answer(QString file_name, int index);
    void open_form();
    void save_prog_num_fields(QString file_name);
    void save_prog_num_table_fields(QString file_name);
    void save_prog_text_fields(QString file_name);
    void save_prog_multi_fields(QString file_name);
private:
    Ui::TrainingFormDialog *ui;
    QWebEngineView web_view;
    QStringList list_task_number;
    QStandardItemModel string_model;
    QString resource_path;
    bool flag_end_try;
};

#endif // TRAININGFORMDIALOG_H