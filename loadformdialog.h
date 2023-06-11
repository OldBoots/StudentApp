#ifndef LOADFORMDIALOG_H
#define LOADFORMDIALOG_H

#include <QDialog>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QWebEngineView>
#include <QMessageBox>
#include <QBuffer>
#include <QRandomGenerator>
#include <QByteArray>

namespace Ui {
class LoadFormDialog;
}

class LoadFormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadFormDialog(QString path_json, QString path_src, QWidget *parent = nullptr);
    ~LoadFormDialog();
private slots:
    void slot_add_tasks();
    void slot_close();
private:
    void load_JSon_data();
    void creat_form();
    void write_form();
    void rand_arr_value(QStringList &list_str, QList <int> &list_index);
    void set_task_answer(QString value, QString field_id);
    void fill_html_28line_task(QJsonObject task);
    void fill_html_multi_task(QJsonObject task);
    void fill_html_table_string_task(QJsonObject task);
    void fill_html_seq_task(QJsonObject task);
    void fill_html_defauld_fields(QJsonObject task);
    void fill_html_comp_task(QJsonObject task);
    void set_field_image(QJsonObject task);
    void fill_html_num_string_task(QJsonObject task);
    void set_field_string(QString value, QString field_id);
    void runJS(QWebEngineView &form, QString js_str);
    void closeEvent (QCloseEvent *event) override;
    QString read_file(QString file_name);
private:
    Ui::LoadFormDialog *ui;
    QString html_form;
    QString path_json;
    QString path_src_form;
    QJsonArray data_json_arr;
    QWebEngineView temp_form;
    int load_stage;
};

#endif // LOADFORMDIALOG_H
