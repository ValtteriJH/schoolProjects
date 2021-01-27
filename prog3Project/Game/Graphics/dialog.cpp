#include "dialog.hh"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("UFO");
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &Dialog::accept);
    connect(ui->pushButtonQuit, &QPushButton::clicked, this, &Dialog::reject);
    connect(ui->pushButtonLore, &QPushButton::clicked, this, &Dialog::onPushButtonLoreClicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onPushButtonLoreClicked(){
    LoreDialog *lw = new LoreDialog();
    lw->exec();
}
