#include "initialization.h"


initialization::initialization()
{
    Q_INIT_RESOURCE(offlinedata);
    QFile mapFile(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    qDebug() << mapFile.size();
    const QString filename(mapFile.fileName());
    QImage map(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    map.load(filename);
}
