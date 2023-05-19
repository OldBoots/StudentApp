#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QWebChannel>

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
    void slot_create_form(QList <int>);
private:
    Ui::TrainingForm *ui;
    QWebEngineView web_view;
};

#endif // TRAININGFORM_H
