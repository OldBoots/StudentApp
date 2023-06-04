#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QMainWindow>
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
#include "closedialog.h"

namespace Ui {
class TrainingForm;
}

class TrainingForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrainingForm(QWidget *parent = nullptr);
    ~TrainingForm();
private slots:
    void slot_show_form();
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
private:
    Ui::TrainingForm *ui;
    QWebEngineView web_view;
    QStringList list_task_number;
    QStandardItemModel string_model;
    QString resource_path;
    bool flag_end_try;
};

#endif // TRAININGFORM_H
