#ifndef DIALOG_HH
#define DIALOG_HH

#include <QDialog>


#include "loredialog.hh"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void onPushButtonLoreClicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_HH
