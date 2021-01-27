#ifndef LOREDIALOG_HH
#define LOREDIALOG_HH

#include <QDialog>

namespace Ui {
class LoreDialog;
}

class LoreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoreDialog(QWidget *parent = nullptr);
    ~LoreDialog();

private:
    Ui::LoreDialog *ui;
};

#endif // LOREDIALOG_HH
