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
    void slot_count_ex();
    void slot_end_try();
private:
    QString read_file(QString path);
    QString set_JS_data(QString file_path, QString value_name, QString value);
    void replace_value_in_str(QString &str, QString value_name, QString value);
    bool check_task_answer(QString file_name, int index);
private:
    Ui::TrainingForm *ui;
    QWebEngineView web_view;
    QStringList list_task_number;
    QStringListModel string_model;
    QString resource_path;
};

#endif // TRAININGFORM_H
