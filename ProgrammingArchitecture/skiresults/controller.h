#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QObject>
#include <QVariant>
#include <exception>
#include <algorithm>
#include <QStringListModel>

#include <datahandler.h>
#include <timet.h>
#include <tablemodel.h>
#include <datatypeconverter.h>
#include "chartmodel.h"
#include "weather.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(TableModel *tbmodel, QStringListModel *rctagModel, ChartModel *chmodel, QObject *parent = nullptr);
    std::vector<QString> getEveryYear();
    Q_INVOKABLE void search(QString state, QString year1, QString year2,
                            QString starttime, QString endtime, QString racetag1,
                            QString racetag2, QString athletename, QString sizeofranking,
                            QString gender, QString choice);

    Q_INVOKABLE void setNewRaceTags(int searchType, QString year1, QString year2);

private:
    DataHandler dataHandler;
    DataTypeConverter dataconverter;

    QStringListModel *racetagModel;
    TableModel *tableModel;
    ChartModel * chartmodel;

    TimeT convertToTimeT(QString str);
    void logError(std::string msg);
    void callShowResultsInQML(int tableType);
    void callShowWeather(Weather weather);

signals:
    void showResults(int tableType);
    void showWeather(QString rain, QString temp, QString snow, QString minTemp, QString maxTemp);
    void badInputSignal(QString message);

};

#endif // CONTROLLER_H
