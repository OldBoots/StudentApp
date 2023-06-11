#ifndef LOADFORM_H
#define LOADFORM_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QWebEngineView>

class LoadForm
{
public:
    LoadForm(QString jSon_file_name, QString src);

private:
    void load_JSon_data();
    void creat_form();
    bool runJS(QWebEngineView &form, QString js_str);
    QString read_file(QString file_name);
private:
    QString html_form;
    QString jSon;
    QString path_src_form;
    QJsonArray data_json_arr;
    QWebEngineView temp_form;
};

#endif // LOADFORM_H
