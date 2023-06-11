#ifndef FORMDIALOG_H
#define FORMDIALOG_H

#include "closedialog.h"
#include <QDialog>
#include <QFile>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QWebEngineView>

namespace Ui {
class FormDialog;
}

class FormDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormDialog(QWidget *parent = nullptr);
    ~FormDialog();
private slots:
    void slot_finished_form_load();
    void slot_end_try();
    void slot_close();
private:
    void show_task_list();
    void load_form();
    void save_progress();
    void load_progress();
    void replace_value_in_str(QString &str, QString value_name, QString value);
    void closeEvent (QCloseEvent *event) override;
//    void link_JS_file(QWebEngineView &web, QString js_file_name);
    QString set_JS_data(QString file_str, QString value_name, QString value);
    QString read_file(QString path);
    bool run_JS_str_wr(QWebEngineView &web, QString js_str, int w_flg);
    QVariant run_JS_str_gd(QWebEngineView &web, QString js_str);
private:
    Ui::FormDialog *ui;
    QString form_src;
    QWebEngineView web_view;
    QStringList list_task_num;
    QStandardItemModel model;
    bool flag_end_try;
};

#endif // FORMDIALOG_H
