#include "loredialog.hh"
#include "ui_loredialog.h"

LoreDialog::LoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoreDialog)
{
    ui->setupUi(this);
    ui->plainTextEdit->setReadOnly(true);
}

LoreDialog::~LoreDialog()
{
    delete ui;
}
