#include "loadformdialog.h"
#include "ui_loadformdialog.h"

LoadFormDialog::LoadFormDialog(QString json, QString src, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFormDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Drawer);
    path_src_form = src;
    path_json = json;
    load_stage = 0;
    creat_form();
    connect(&temp_form, SIGNAL(loadFinished(bool)), SLOT(slot_add_tasks()));
    connect(ui->butt_cancel, SIGNAL(clicked(bool)), SLOT(slot_close()));
}

void LoadFormDialog::load_JSon_data()
{

    QFile file(path_json);
    QString data_str;
    QJsonDocument data_json;
    file.open(QIODevice::ReadOnly);
    data_str = file.readAll();
    file.close();
    data_json = QJsonDocument::fromJson(data_str.toUtf8());
    data_json_arr = data_json.array();
}

void LoadFormDialog::slot_add_tasks()
{
    QJsonValue value;
    QJsonObject obj;
    for(int i = 0; i < data_json_arr.size(); i++){
        value = data_json_arr[i];
        obj = value.toObject();
        ui->progressBar->setValue(qCeil((100.0 / (double)data_json_arr.size()) * (double)++load_stage));
        switch (obj["type"].toInt()) {
        case 1:
            runJS(temp_form, "create_task_number(" + QString::number(obj["id"].toInt()) + ", " + QString::number(i + 1) + ")");
            fill_html_num_string_task(obj);
            break;
        case 2:
            runJS(temp_form, "create_task_string(" + QString::number(obj["id"].toInt()) + ", " + QString::number(i + 1) + ")");
            fill_html_num_string_task(obj);
            break;
        case 3:
            runJS(temp_form, "create_task_comp(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["answer"].toArray().size()) + ", " + QString::number(i + 1) + ")");
            fill_html_comp_task(obj);
            break;
        case 4:
            runJS(temp_form, "create_task_seq(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["options"].toArray().size()) +  ", " + QString::number(i + 1) + ")");
            fill_html_seq_task(obj);
            break;
        case 5:
            runJS(temp_form, "create_task_table_string(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["count_rows"].toInt()) + ","
                                 + QString::number(obj["count_cols"].toInt()) +  ", " + QString::number(i + 1) + ")");
            fill_html_table_string_task(obj);
            break;
        case 6:
            runJS(temp_form, "create_task_multi(" + QString::number(obj["id"].toInt()) + ","
                                 + QString::number(obj["options"].toArray().size()) +  ", " + QString::number(i + 1) + ")");
            fill_html_multi_task(obj);
            break;
        case 7:
            runJS(temp_form, "create_task_28line(" + QString::number(obj["id"].toInt()) +  ", " + QString::number(i + 1) + ")");
            fill_html_28line_task(obj);
            break;
        default:
            QMessageBox m_box(QMessageBox::Warning, tr("Ошибка"), tr("Не получается определить тип задания."));
            m_box.setWindowFlags(Qt::SubWindow);
            m_box.exec();
            break;
        }
    }
    write_form();
}

void LoadFormDialog::slot_close()
{
    QMessageBox m_box(QMessageBox::NoIcon, tr("Предупреждение"), tr("Вы хотите прекратить загрузку бланка?"), QMessageBox::Ok | QMessageBox::Cancel);
    m_box.setWindowFlags(Qt::SubWindow);
    m_box.setButtonText(QMessageBox::Ok, "Да");
    m_box.setButtonText(QMessageBox::Cancel, "Нет");
    if(m_box.exec()){
        this->reject();
    }
}

void LoadFormDialog::fill_html_28line_task(QJsonObject task)
{
    set_field_string(task["text_ex"].toString(), "text_" + QString::number(task["id"].toInt()));
    set_field_string("<br>5\'- " + task["codogenic"].toString() + " -3\'", "text_" + QString::number(task["id"].toInt()));
    set_field_string("<br>3\'- " + task["transcribed"].toString() + " -5\'", "text_" + QString::number(task["id"].toInt()));
    set_field_string(task["iRNA"].toString(), "answer_iRNA_" + QString::number(task["id"].toInt()));
    set_field_string(task["polypeptide"].toString(), "answer_" + QString::number(task["id"].toInt()));
    if(task["image"].toString().size()){
        set_field_image(task);
    }
}

void LoadFormDialog::fill_html_multi_task(QJsonObject task)
{
    fill_html_defauld_fields(task);
    QJsonArray options = task["options"].toArray();
    QJsonArray answers = task["answer"].toArray();
    QStringList list_options, list_answers;
    QString answer_str;
    for(int i = 0; i < options.size(); i++){
        list_options << options[i].toString();
    }
    for(int i = 0; i < answers.size(); i++){
        answer_str += answers[i].toString();
    }
    qDebug() << list_answers << list_options;
    QString answer_num_str;
    for(int i = 0; i < list_options.size(); i++){
        set_field_string(list_options[i], "opt_" + QString::number(task["id"].toInt()) + "_" + QString::number(i));
        if(answer_str.contains(list_options[i])){
            answer_num_str += QString::number(i);
        }
    }
    set_field_string(answer_num_str, "answer_" + QString::number(task["id"].toInt()));
}

void LoadFormDialog::fill_html_table_string_task(QJsonObject task)
{
    fill_html_defauld_fields(task);
    QJsonObject arr_table = task["table"].toObject();
    for(int i = 0; i < task["count_rows"].toInt(); i++){
        for(int j = 0; j < task["count_cols"].toInt(); j++){
            if(arr_table[QString::number(i) + QString::number(j)].toString() != "~ans~"){
                set_field_string(arr_table[QString::number(i) + QString::number(j)].toString(), "table_"
                                                                                                    + QString::number(task["id"].toInt()) + "_"
                                                                                                    + QString::number(i) + "_"
                                                                                                    + QString::number(j));
            }else{
                runJS(temp_form, "add_input(" + QString::number(task["id"].toInt()) +", " + QString::number(i) + ", " + QString::number(j) + ");");
            }
        }
    }
}

void LoadFormDialog::fill_html_comp_task(QJsonObject task)
{
    QString answer_str = "";
    set_field_string(task["text_ex"].toString(), "text_" + QString::number(task["id"].toInt()));
    if(task["image"].toString().size()){
        set_field_image(task);
    }
    QJsonArray arr_answ = task["answer"].toArray();
    QJsonObject single_answ;
    QStringList list_value;
    QList <int> list_index;
    for(int i = 0; i < arr_answ.size(); i++){
        single_answ = arr_answ[i].toObject();
        foreach(const QString& key, single_answ.keys()) {
            QJsonValue value = single_answ.value(key);
            set_field_string(key, "list_A_" + QString::number(task["id"].toInt()) + "_" + QString::number(i));
            list_value.push_back(value.toString());
        }
        list_index.push_back(i);
    }
    rand_arr_value(list_value, list_index);
    for(int i = 0; i < list_value.size(); i++){
        set_field_string(list_value[i], "list_1_" + QString::number(task["id"].toInt()) + "_" + QString::number(i));
        answer_str += QString::number(list_index[i] + 1);
    }
    set_field_string(answer_str, "answer_" + QString::number(task["id"].toInt()));
    set_field_string(task["solution"].toString(), "solution_" + QString::number(task["id"].toInt()));
}

void LoadFormDialog::fill_html_seq_task(QJsonObject task)
{
    fill_html_defauld_fields(task);
    QJsonArray arr_options = task["options"].toArray();
    QJsonObject single_option;
    for(int i = 0; i < arr_options.size(); i++){
        single_option = arr_options[i].toObject();
        foreach(const QString& key, single_option.keys()) {
            QJsonValue value = single_option.value(key);
            set_field_string(value.toString(), "list_1_" + QString::number(task["id"].toInt()) + "_" + QString::number(i));
        }
    }
}

void LoadFormDialog::fill_html_num_string_task(QJsonObject task){
    set_field_string(task["text_ex"].toString(), "text_" + QString::number(task["id"].toInt()));
    if(task["image"].toString().size()){
        set_field_image(task);
    }
    set_field_string(task["answer"].toString(), "answer_" + QString::number(task["id"].toInt()));
    set_field_string(task["solution"].toString(), "solution_" + QString::number(task["id"].toInt()));
}

void LoadFormDialog::fill_html_defauld_fields(QJsonObject task)
{
    set_field_string(task["text_ex"].toString(), "text_" + QString::number(task["id"].toInt()));
    if(task["image"].toString().size()){
        set_field_image(task);
    }
    set_field_string(task["answer"].toString(), "answer_" + QString::number(task["id"].toInt()));
    set_field_string(task["solution"].toString(), "solution_" + QString::number(task["id"].toInt()));
}

void LoadFormDialog::set_field_image(QJsonObject task)
{
    QByteArray base64 = task.value("image").toString().toUtf8();
    if(base64.size()!= 0){
        QPixmap testt;
        testt.loadFromData(QByteArray::fromBase64(base64), task.value("image_type").toString().toLocal8Bit().data());
        QByteArray bytes;
        QBuffer buffer(&bytes);
        buffer.open(QIODevice::WriteOnly);
        testt.save(&buffer, "PNG");
        // to base64
        QByteArray ba = bytes.toBase64();

        QString html;
        html += QString("<img src='data:image/png;base64,%1'/>").arg(QString(ba));
        bool flag_finish = false;
        temp_form.page()->runJavaScript("document.getElementById(\"image_" + QString::number(task["id"].toInt()) + "\").innerHTML += \"" + html + "\";",
                                        [&](QVariant)->void{
                                            flag_finish = true;
                                        });
        while(!flag_finish){
            QApplication::processEvents();
        }
    }
}

void LoadFormDialog::creat_form()
{
    load_JSon_data();
    temp_form.load(path_src_form + "BlankFormTemplate.html");
}

void LoadFormDialog::write_form()
{
    QString temp_html;
    temp_form.page()->runJavaScript("document.documentElement.innerHTML", [&]
                                    (QVariant result){
                                        temp_html = result.toString();
                                    });
    while(temp_html.isEmpty()){
        QApplication::processEvents();
    }
    QFile file(path_src_form + "Form.html");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly);
    stream << "<!DOCTYPE html>" << temp_html << "</html>";
    file.close();
    this->accept();
}

void LoadFormDialog::rand_arr_value(QStringList &list_str, QList <int> &list_index)
{
    for(int i = 0; i < list_str.size() / 3; i++){
        int index1, index2;
        index1 = QRandomGenerator::global()->bounded(0, list_str.size());
        index2 = QRandomGenerator::global()->bounded(0, list_str.size());
        qSwap(list_str[index1], list_str[index2]);
        qSwap(list_index[index1], list_index[index2]);
    }
}

void LoadFormDialog::set_field_string(QString value, QString field_id)
{
    bool ok = false;
    qDebug() << field_id;
    temp_form.page()->runJavaScript("document.getElementById(\"" + field_id + "\").innerHTML += \"" + value + "\";",
                                    [&](QVariant){
                                        ok = true;
                                    });
    while(!ok){
        QApplication::processEvents();
    }
}

void LoadFormDialog::runJS(QWebEngineView &form, QString js_str)
{
    bool ok = false;
    qDebug() << js_str;
    form.page()->runJavaScript(js_str, [&]
                               (QVariant res){
                                   ok = res.toBool();
                                   qDebug() << ok;
                               });
    while(!ok){
        QApplication::processEvents();
    }
}

void LoadFormDialog::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    slot_close();
}

QString LoadFormDialog::read_file(QString file_name)
{
    QString str;
    QFile file(path_src_form + file_name);
    file.open(QIODevice::ReadOnly);
    str = file.readAll();
    file.close();
    return str;
}

LoadFormDialog::~LoadFormDialog()
{
    delete ui;
}
