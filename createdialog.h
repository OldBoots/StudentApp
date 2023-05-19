#ifndef CREATEDIALOG_H
#define CREATEDIALOG_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QUrl>
#include <QTextStream>
#include <QWebEngineView>
#include <QHBoxLayout>
#include <QElapsedTimer>
#include "trainingform.h"

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
signals:
    void sign_task_processing_completed();
    void sign_task_parsing_completed();
private:
    QString load_file(QString path);
    void load_url();
    QString set_JS_data(QString file);
private:
    Ui::CreateDialog *ui;
    QWebEngineView web_page;
    QStringList list_url;
    int count_quest;
    int num_quest;
    int current_type;
    QString body_html;
    QList<QHBoxLayout*> layout_list;
    int cur_num;
    QElapsedTimer waiting_timer;
};

#endif // CREATEDIALOG_H
