#include "loadform.h"

LoadForm::LoadForm(QString jSon_file_name, QString src)
{
    jSon = jSon_file_name;
    path_src_form = src;
    QObject::connect(&temp_form, SIGNAL(), SLOT());
}

void LoadForm::load_JSon_data()
{
    QFile file(jSon);
    QString data_str;
    QJsonDocument data_json;
    file.open(QIODevice::ReadOnly);
    data_str = file.readAll();
    file.close();
    data_json = QJsonDocument::fromJson(data_str.toUtf8());
    data_json_arr = data_json.array();
}

void LoadForm::add_task()
{
    QJsonValue value;
    QJsonObject obj;
    for(int i = 0; i < data_json_arr.size(); i++){
        value = data_json_arr[i];
        obj = value.toObject();
        switch (obj["type"].toInt()) {
        case 1:
            runJS(temp_form, "create_task_number(" + QString::number(obj["id"].toInt()) + ")");
            break;
        case 2:
            runJS(temp_form, "create_task_string(" + QString::number(obj["id"].toInt()) + ")");
            break;
        case 3:
            runJS(temp_form, "create_task_comp(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["options"].toArray().size()) + ")");
            break;
        case 4:
            runJS(temp_form, "create_task_seq(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["options"].toArray().size()) + ")");
            break;
        case 5:
            runJS(temp_form, "create_task_table_string(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["count_rows"].toInt()) + ","
                                 + QString::number(obj["count_columns"].toInt()) + ")");
            break;
        case 6:
            runJS(temp_form, "create_task_multi(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["options"].toArray().size()) + ")");
            break;
        case 7:
            runJS(temp_form, "create_task_28line(" + QString::number(obj["id"].toInt()) + ")");
            break;
        default:
            break;
        }
    }
}

void LoadForm::creat_form()
{
    QFile file(path_src_form + "Form.html");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);
    stream << read_file("BlankFormTemplate.html");
    file.close();
    temp_form.load(path_src_form + "Form.html");


}

bool LoadForm::runJS(QWebEngineView &form, QString js_str)
{
    bool ok;
    form.page()->runJavaScript(js_str, [&]
                               (QVariant result){
                                   ok = result.toBool();
                               });
    while(!ok){}
}

QString LoadForm::read_file(QString file_name)
{
    QString str;
    QFile file(path_src_form + file_name);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}
