
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    // Редактируем внешний вид главной окна
    // Удаляем поля у окна
    setWindowFlags(Qt::FramelessWindowHint);
    // Скругляем углы и задаем цвет
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("background:transparent;");
    // Применяем CSS стили для оформления окна
    ui->frame->setStyleSheet(load_style(":/StyleWindow.css"));
    // Указываем путь к в которой будут храниться
    resource_path = "C:/Qt/project/StudentApp/";
    // Применяем CSS стили для оформления кнопачек
    ui->butt_create->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_open->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_close->setStyleSheet(load_style(":/StyleButtMenu.css"));
    ui->butt_continue->setStyleSheet(load_style(":/StyleButtMenu.css"));
    // Привязываем событие нажатия кнопок к слотам
    connect(ui->butt_close, SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->butt_create, SIGNAL(clicked(bool)), SLOT(slot_create()));
    connect(ui->butt_continue, SIGNAL(clicked(bool)), SLOT(slot_continue()));
}


Dialog::~Dialog() // Диструктор класса
{
    delete ui;
}

void Dialog::slot_create() // Слот создания тренировочной формы
{
    // Инициализируем и открываем окно создания тренировочного бланка
    CreateDialog create_dialog;
    if(create_dialog.exec()){
        // Инициализируем и открываем окно решения бланка
        TrainingFormDialog training_form;
        training_form.exec();
    }
}

void Dialog::slot_open()
{

}

void Dialog::slot_continue() // Слот продолжения решения бланка
{
    // Проверяем существует ли файл с тренировочным бланком
    if(QFileInfo::exists(resource_path + "html.html")){
        // Инициализируем и открываем окно решения бланка
        TrainingFormDialog training_form;
        training_form.exec();
    }else{
        // Иначе выводим предупреждение
        QMessageBox m_box(QMessageBox::Warning, tr("Предупреждение"), tr("Тренировочный бланк отсутствует."));
        m_box.setWindowFlags(Qt::SubWindow);
        m_box.setInformativeText("Создайте новый тренировойчный бланк.");
        m_box.exec();
    }
}

QString Dialog::load_style(QString path) // Метод для считывания CSS кода из файла в строку
{
    QString str;
    // Указываем путь к файлу
    QFile file(path);
    // Открываем файл для чтения
    file.open(QIODevice::ReadOnly);
    // Записываем содержимое файла в строку
    str = file.readAll();
    // Закрываем файл
    file.close();
    return str;
}

