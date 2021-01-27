#ifndef CHARTMODEL_H
#define CHARTMODEL_H

#include <vector>

#include "datahandler.h"

class ChartModel : public QObject
{
    Q_OBJECT

signals:
    void sendData(QVector<QVector<QString>> data);


public:
    ChartModel(QObject*parent = nullptr);

    void addAtheleteDevelopmentData(QVector<QVector<QString>> data);

};

#endif // CHARTMODEL_H
