#ifndef ENDINGDIALOG_HH
#define ENDINGDIALOG_HH

#include <QDialog>

namespace Ui {
class EndingDialog;
}

class EndingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EndingDialog(QWidget *parent = nullptr, int num = 0);
    ~EndingDialog();

private:
    Ui::EndingDialog *ui;
};

#endif // ENDINGDIALOG_HH
