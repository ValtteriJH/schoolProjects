#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include <QObject>
#include <QApplication>
#include <QImage>
#include <QDebug>
#include <QFile>
#include <Graphics/mainwindow.hh>
/**
 * @brief The initialization class
 * Sets up map and window offlinedata
 */

class initialization : public QObject
{
    Q_OBJECT

public:
    initialization();


public slots:
    //void

};

#endif // INITIALIZATION_H
