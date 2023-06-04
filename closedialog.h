#ifndef CLOSEDIALOG_H
#define CLOSEDIALOG_H

#include <QDialog>

namespace Ui {
class CloseDialog;
}

class CloseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloseDialog(QWidget *parent = nullptr);
    ~CloseDialog();
    bool get_flag();
private slots:
    void slot_end_close();
private:
    Ui::CloseDialog *ui;
    bool flag_end_try;
};

#endif // CLOSEDIALOG_H
