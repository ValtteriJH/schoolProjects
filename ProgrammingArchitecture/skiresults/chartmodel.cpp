#include <QtCharts>
#include <tuple>
#include <algorithm>
#include <QDebug>
#include "chartmodel.h"

ChartModel::ChartModel(QObject *parent) : QObject(parent)
{

}


void ChartModel::addAtheleteDevelopmentData(QVector<QVector<QString>> data)
{
    emit sendData(data);
}
