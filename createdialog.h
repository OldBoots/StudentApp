#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QUrl>
#include <QTextStream>
#include <QWebEngineView>
#include <QHBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include <QProgressBar>

namespace Ui {
class CreateDialog;
}

class CreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDialog(QWidget *parent = nullptr);
    ~CreateDialog();
private slots:
    void slot_plus();
    void slot_minus();
    void slot_create_form();
    void slot_parse_tasks();
    void slot_task_processing();
    void slot_show_web_page();
    void slot_waiting_overrun();
//    void slot_load_page();
signals:
    void sign_task_processing_completed();
    void sign_task_parsing_completed();
    void sign_stage_change(int percent);
private:
    QString read_file(QString path);
    QString set_JS_data(QString file_path, QString value_name, QString value);
    void replace_value_in_str(QString &str, QString value_name, QString value);
    void remove_last_try();
    void closeEvent (QCloseEvent *event) override;
//    void load_url();
private:
    Ui::CreateDialog *ui;
    QWebEngineView web_page;
    QWebEngineView temp_page;
    QStringList list_url;
    int count_quest;
    int num_quest;
    QString body_html;
    QList<QHBoxLayout*> layout_list;
    int cur_num;
    QTimer timer_waiting;
    bool flag_overrun;
    QString resource_path;
    QProgressBar progress_bar;
    int stage;
};

#endif // CREATEDIALOG_H
