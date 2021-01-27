#include "creategame.hh"
#include "maincity.hh"
#include "../Graphics/mainwindow.hh"

namespace Junttarit{

    std::shared_ptr<Interface::ICity> creategame(std::shared_ptr<MainWindow> w) {

    std::shared_ptr<Junttarit::mainCity> ampere(new Junttarit::mainCity(w));
    if (w->isVisible()){
    CourseSide::Logic *logic = new CourseSide::Logic();
    logic->readOfflineData(":/offlinedata/offlinedata/final_bus_liteN.json", ":/offlinedata/offlinedata/full_stations_kkj3.json");
    logic->takeCity(ampere);
    QTime time;
    logic->setTime(time.currentTime().hour(),time.currentTime().minute());
    logic->finalizeGameStart();
    return ampere;
    }
    else{return nullptr;}
}
}
