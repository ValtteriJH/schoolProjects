#ifndef MAINCITY_HH
#define MAINCITY_HH
#include "../Course/CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/istop.hh"
#include "../Course/CourseLib/actors/nysse.hh"
#include "Graphics/mainwindow.hh"
#include "../Course/CourseLib/actors/passenger.hh"
#include "QElapsedTimer"

#include <QTime>
#include <QDebug>

#include "tilasto.hh"


namespace Junttarit{

/**
 * @brief The mainCity class
 * mainCity class inherits the ICity interface, and defines it's virtual functions.
 * This class' main purpose is to use mainWindow, to perform the needed visual changes utilizing QScene.
 *
 * City also defines gameStart and gameOver, sets up gameClock, and background.
 * Actors are added and removed utilizing this class.
 */

class mainCity : public Interface::ICity
{
public:
    mainCity(std::shared_ptr<MainWindow> window);

    void setBackground(QImage &basicbackground, QImage &bigbackground) override;

    void setClock(QTime clock) override;

    void addStop(std::shared_ptr<Interface::IStop> stop) override;

    void startGame() override;

    void addActor(std::shared_ptr<Interface::IActor> newactor) override;

    void removeActor(std::shared_ptr<Interface::IActor> actor) override;

    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;

    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;

    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;
    void gameOver();

    bool isGameOver() const override;

    void endgameCheck();


private:

    QElapsedTimer _citytime = QElapsedTimer();

    QTime _cityClock;
    std::shared_ptr<MainWindow> window_;

    QImage _smolBackground;
    QImage _bigBackground;
    // Map (key= unsigned int ID, pair(sharedPtr<IActoritem>, type))
    // std::pair<int, int> asd = std::make_pair(8,8);
    /*
    Stop = 0
    Player = 1
    Bus = 2
    Passenger = 3
    Tier = 4 (under construction)
    */

    int score_;

    double finishTime_ = 0;

    std::map<std::shared_ptr<Interface::IActor>, std::pair<int, int>> _allActors;

    std::map<std::shared_ptr<Interface::IStop>, std::pair<int, int>> _allStops;

    int _actorcount = 10000;        // id count started high in order to avoid matching id's with stops.

    bool _gameOver = true;

};
}
#endif // MAINCITY_HH
