#include "endingdialog.hh"
#include "ui_endingdialog.h"

EndingDialog::EndingDialog(QWidget *parent, int num) :
    QDialog(parent),
    ui(new Ui::EndingDialog)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
    ui->lcdNumber->display(num);
    ui->lcdNumber->setPalette(Qt::red);
    connect(ui->pushButton, &QPushButton::clicked, this, &EndingDialog::close);
}

EndingDialog::~EndingDialog()
{
    delete ui;
}
