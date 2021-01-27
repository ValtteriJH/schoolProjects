#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include "Graphics/mainwindow.hh"
#include "Core/creategame.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<Junttarit::MainWindow> window = std::make_shared<Junttarit::MainWindow>();
    Junttarit::creategame(window);
    return a.exec();
}
