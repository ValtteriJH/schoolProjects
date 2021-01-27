#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "../CourseLib/graphics/simpleactoritem.hh"
#include "../CourseLib/core/logic.hh"
#include "../CourseLib/interfaces/icity.hh"
#include "../Course/CourseLib/interfaces/iactor.hh"
#include "nyssegraphics.hh"

#include "Actors/teekkari.h"
#include "Graphics/UFOGraphics.h"
#include "stopgraphics.hh"
#include "passengergraphics.hh"
#include "dialog.hh"
#include "endingdialog.hh"

#include <QElapsedTimer>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QGraphicsView>
#include <QDebug>

namespace Ui {
class MainWindow;
}

namespace Junttarit {



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow is where all the graphics happen.
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /**
     * @brief setPicture sets the background for the graphics scene
     * @param img
     */
    void setPicture(QImage &img);

    /**
     * @brief addActor Adds a graphics item, that represents an actor from logic.
     * @param obj The actor that needs to be represented
     * @param id needed to make the graphic unique to a single actor.
     * @param type id The actors id, needed to recognize the actor so the correct graphic can be loaded.
     */
    void addActor(std::shared_ptr<Interface::IActor> obj, int id, int type);

    /**
     * @brief addStop Adds a stop. Stops have a different interface so a seperate function is needed.
     * @param stop The stop that needs to be represeneted.
     * @param id The stops unique id.
     */
    void addStop(std::shared_ptr<Interface::IStop> stop, int id);

    /**
     * @brief removeActor Removes the actors graphic from the scene.
     * @param mover_id The unique id of the actor, so the correct graphic can be deleted.
     * @return bool to check if removal was succesful.
     */
    bool removeActor(int mover_id);
    /**
     * @brief removeStop Removoes stop form the scene.
     * @param stop_id Stops unique id so it can be recognized.
     */
    void removeStop(int stop_id);

    /**
     * @brief moveActor Moves all the actors that need to be moved in the scene.
     * @param id The id of the actor that needs to be moved
     * @param x new x
     * @param y new y
     */
    void moveActor(int id, int x, int y);

    /**
     * @brief setTick sets the tick time for the city
     * @param t
     */
    void setTick(int t);

    /**
     * @brief keyPressEvent Event to recognize the movement inputs of the player.
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief updateGameState Checks if the game is over
     * @param i updates the citys score
     * @return
     */
    bool updateGameState(int &i);

    /**
     * @brief endGame Opens the ending dialog
     * @param score tells the ending dialog the score.
     */
    void endGame(int score);

    /**
     * @brief setTime sets the time for the window.
     * @param time
     */
    void setTime(const std::shared_ptr<QElapsedTimer> time);

    /**
     * @brief checkPlayerCollisions function that checks the collision of the playergrahics and a stop.
     */
    void checkPlayerCollisions();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *map_;

    QTimer *timer;
    QVector<QGraphicsItem*> movers_;
    QVector<QGraphicsItem*> stops_;

    std::map<int, std::shared_ptr<QGraphicsItem>> actorMap_;

    std::map<int, std::pair<StopGraphics*, std::shared_ptr<Interface::IStop>>> stopMap_;



    QGraphicsItem* playerGraphics_;

    int width_ = 1095; //pxls
    int height_ = 592;
    int t_ = 100; //ms
    int points_ = 0;
    int time = 0;
    int dirx_ = 0;
    int diry_ = 0;

    int capturedHumans_ = 0;

    std::shared_ptr<Junttarit::Teekkari> player_;

    std::shared_ptr<QElapsedTimer> time_;

    QGraphicsItem* last_;

    int counter_ = 0;
    std::set<int> history_;

    bool game_is_ending =false;

// std::map< int, std::pair<NysseGraphics*, std::shared_ptr<Interface::IActor>> > nysseMap_;

 //   std::map<int, std::pair<PassengerGraphics*,std::shared_ptr<Interface::IActor>>> passengerMap_;


};



} //namespace
#endif // MAINWINDOW_HH
