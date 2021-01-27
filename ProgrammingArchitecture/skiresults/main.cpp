#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>

#include "controller.h"
#include "datahandlertest.h"
#include "tablemodel.h"
#include "chartmodel.h"


int main(int argc, char *argv[])
{
    // TESTS
    DataHandlerTest tester;
    tester.test_all();
    // TESTS END

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // For chartview
    ChartModel chmodel;
    engine.rootContext()->setContextProperty("chartmodel",&chmodel);

    // Tableview model
    TableModel tbmodel;
    engine.rootContext()->setContextProperty("tablemodel",&tbmodel);
    //

    // Combobox 2
    QStringListModel racesStrList;
    engine.rootContext()->setContextProperty("rctagmodel",&racesStrList);

    // Controller
    Controller controller(&tbmodel,&racesStrList, &chmodel);
    engine.rootContext()->setContextProperty("controller",&controller);
    //

    // Combobox year model
    auto years = controller.getEveryYear();
    QStringList yearList;
    for(auto year : years)
    {
        yearList.append(year);
    }
    engine.rootContext()->setContextProperty("yearsModel", QVariant::fromValue(yearList));
    //


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
