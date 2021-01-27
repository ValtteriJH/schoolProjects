#include "maincity.hh"


Junttarit::mainCity::mainCity(std::shared_ptr<MainWindow> parent)
{
    window_ = parent;
}

void Junttarit::mainCity::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    _smolBackground = basicbackground;
    _bigBackground = bigbackground;
}

void Junttarit::mainCity::setClock(QTime clock)
{
    _cityClock = clock;
}

void Junttarit::mainCity::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int id = stop->getId();
    std::shared_ptr<Interface::IActor> temp = std::dynamic_pointer_cast<Interface::IActor> (stop);
    _allActors[temp] = std::make_pair(id, 0); // stops in allActors
    _allStops[stop] = std::make_pair(id, 0);
    window_->addStop(stop,id);


}
void Junttarit::mainCity::startGame()
{
    // Logic calls before game start, set something else up here if you want.

    _citytime.start();
    window_->setTime(std::make_shared<QElapsedTimer>(_citytime));
    _gameOver = false;
}

// Interface for security. Overloading the function for different interface types.
void Junttarit::mainCity::addActor(std::shared_ptr<Interface::IActor> newactor)
{

    std::shared_ptr<CourseSide::Nysse> busPtr;
    std::shared_ptr<CourseSide::Stop> stopPtr;
    std::shared_ptr<CourseSide::Passenger> passengerPtr;

    std::shared_ptr<Interface::IActor> testPtr;

    int id = _actorcount;


        if ((busPtr = std::dynamic_pointer_cast<CourseSide::Nysse>(newactor))){

            _allActors[newactor] = std::make_pair(id, 2);
            window_->addActor(busPtr, id, 2);
        }
        else if ((passengerPtr = std::dynamic_pointer_cast<CourseSide::Passenger>(newactor))){
            _allActors[newactor] = std::make_pair(id, 3);
            window_->addActor(newactor, id, 3);

        }else if((stopPtr = std::dynamic_pointer_cast<CourseSide::Stop>(newactor))) {
            addStop(stopPtr);
            id = stopPtr->getId();


        }
    _actorcount++;

}

void Junttarit::mainCity::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    int id = _allActors[actor].first;
    int type = _allActors[actor].second;
    std::shared_ptr<CourseSide::Stop> stopPtr;
    actor->remove();

    if (type == 0){
        window_->removeStop(id);
        _allStops.erase(stopPtr); // stop ptrs included in allActors
        _allActors.erase(actor);
    }else if(type == 2){
        window_->removeActor(id);
        _allActors.erase(actor);
    }else if(type == 3){
        window_->removeActor(id);
        _allActors.erase(actor);

    }else{
        qDebug() << "Tried to remove unidentified actor from city";
    }


}

void Junttarit::mainCity::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    //this->removeActor(actor);
    actor->isRemoved();
}

void Junttarit::mainCity::endgameCheck(){
    if(window_->updateGameState(score_)){
        int time =_citytime.elapsed();
        finishTime_ = time/60;
        gameOver();

    }
}

void Junttarit::mainCity::actorMoved(std::shared_ptr<Interface::IActor> actor)
{

    int id = _allActors[actor].first;
    int nx = actor->giveLocation().giveX();
    int ny = actor->giveLocation().giveY();
    endgameCheck();
    window_->moveActor(id, nx, ny);
}

bool Junttarit::mainCity::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    std::shared_ptr<CourseSide::Stop> stopPtr = std::dynamic_pointer_cast<CourseSide::Stop> (actor);
    if(_allActors.find(actor) == _allActors.end() && _allStops.find(stopPtr) == _allStops.end()){
        return false;
    }else{
        return true;
    }
}
/**
 * @brief getNearbyActors returns actors that are close to given position.
 * @param loc Location for getting the actors close to it.
 * @pre City is in gamestate.
 * @return Vector containing actors close to the location, that pass `getLocation().isClose(loc) == true`.
 * @post Exception guarantee: strong.
 */
std::vector<std::shared_ptr<Interface::IActor> > Junttarit::mainCity::getNearbyActors(Interface::Location loc) const
{
    {
        std::vector<std::shared_ptr<Interface::IActor> > result;

        for ( auto it = _allActors.begin(); it != _allActors.end(); ++it) {
            if (loc.isClose(it->first->giveLocation())) {
                result.push_back(it->first);
            }
        }
        return result;
    }
}

bool Junttarit::mainCity::isGameOver() const
{
    return _gameOver;
}
void Junttarit::mainCity::gameOver(){

    _gameOver = true;

}
