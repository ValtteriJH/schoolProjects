#include "mainwindow.hh"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QtGui>

const int PADDING = 10;

namespace Junttarit {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Dialog dialog;
    int dialogcode = dialog.exec();
    if (dialogcode == QDialog::Accepted){
        ui->setupUi(this);
        this->setWindowTitle("North Korean UFO's vs TKL");
        this->setFixedSize(width_ + 200, height_ + 100);
        //placing
        ui->graphicsView->setFixedSize(width_ + PADDING, height_ + PADDING);
        ui->label->move(width_ + 4*PADDING, PADDING);
        ui->label_2->move(width_ + 4*PADDING, 5*PADDING);
        ui->lcdNumberGameTime->move(width_ + 4*PADDING, 3*PADDING);
        ui->lcdNumberScore->move(width_ + 4*PADDING, 7*PADDING);
        //colors
        ui->lcdNumberGameTime->setPalette(Qt::black);
        ui->lcdNumberScore->setPalette(Qt::green);

        map_ = new QGraphicsScene(this);
        ui->graphicsView->setScene(map_);
        map_->setSceneRect(0,0,width_,height_);

        QImage bg;
        bg.load(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
        QImage& bgr = bg;
        this->setPicture(bgr);

        Teekkari player(3328719, 6895872);
        player_ = std::make_shared<Teekkari>(player);

        playerGraphics_ = new Junttarit::UFOGraphics(player_->giveLocation().giveX(), player_->giveLocation().giveY(), player_);

        playerGraphics_->setZValue(1);
        map_->addItem(playerGraphics_);

        this->show();
    } else{
        parent->close();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setPicture(QImage &img)
{
    map_->setBackgroundBrush(img);
}

void MainWindow::addActor(std::shared_ptr<Interface::IActor> obj, int id, int type)
{

    if (type == 2)
    {
        std::shared_ptr<QGraphicsItem> nNysse (new NysseGraphics(obj));
        nNysse->setZValue(0.5);
        map_->addItem(nNysse.get());
        last_ = nNysse.get();
        actorMap_[id] = nNysse;



    }else if (type == 3){

        std::shared_ptr<QGraphicsItem> nPassenger (new PassengerGraphics(obj, id));
        nPassenger->setZValue(0.5);
        map_->addItem(nPassenger.get());
        last_ = nPassenger.get();
        actorMap_[id] = nPassenger;
        counter_++;
        auto search =  history_.find(id);
        if (search != history_.end()){
            qDebug() << "Duplicate adding";
        }
        history_.insert(id);
        qDebug() << "Total passengers: " << counter_ << "Passenger id: " << id;
    }
}

void MainWindow::addStop(std::shared_ptr<Interface::IStop> stop, int id)
{

    StopGraphics* stopGraphic = new StopGraphics(stop);
    stopMap_[id] = std::make_pair(stopGraphic, stop);
    stopMap_[id].first->setZValue(0.1);
    map_->addItem(stopGraphic);

}

bool MainWindow::removeActor(int id)
{
    std::shared_ptr<QGraphicsItem> objPtr = actorMap_[id];
    map_->removeItem(objPtr.get());
    std::shared_ptr<NysseGraphics> nyssePtr;
    std::shared_ptr<PassengerGraphics> passengerPtr;

    if((nyssePtr = std::dynamic_pointer_cast<NysseGraphics>(objPtr))){

        bool test1=nyssePtr->related_nysse()->isRemoved();
        bool test2=nyssePtr->related_nysse()->isRemoved();
        if (test1 != test2){
            actorMap_.erase(id);
            qDebug() << "Nysse remove succesful!";}
        return true;

    }
    if((passengerPtr = std::dynamic_pointer_cast<PassengerGraphics>(objPtr))){

        bool test1=passengerPtr->getRelated_passenger()->isRemoved();
        bool test2=passengerPtr->getRelated_passenger()->isRemoved();
        if (test1 != test2){
            actorMap_.erase(id);
        }
     return true;
}
return false;
}

void MainWindow::removeStop(int stop_id)
{

    stopMap_.erase(stop_id);
    map_->removeItem(stopMap_[stop_id].first);

}

void MainWindow::moveActor(int id, int x, int y)
{


    std::shared_ptr<PassengerGraphics> passengerPtr;
    std::shared_ptr<QGraphicsItem> objPtr = actorMap_[id];

    if((passengerPtr = std::dynamic_pointer_cast<PassengerGraphics>(objPtr))){
        passengerPtr->move();
    }else{
        actorMap_[id]->setX(x);
        actorMap_[id]->setY(y);
    }
}

void MainWindow::setTick(int t)
{
    this->t_ = t;
}

void MainWindow::checkPlayerCollisions(){
    QList<QGraphicsItem*> list = playerGraphics_->collidingItems() ;

    foreach(QGraphicsItem* i , list)
    {
        i = dynamic_cast<StopGraphics*>(i);
        if (i)
        {
            auto stop = dynamic_cast<StopGraphics*>(i)->related_stop();
            std::shared_ptr<CourseSide::Stop> concStop = std::dynamic_pointer_cast<CourseSide::Stop>(stop);
            std::weak_ptr<Interface::IPassenger> pass;


            auto passengers = concStop->getPassengers();
            for(unsigned long i=0;i < passengers.size();i++)
            {
                pass = passengers[i];
                concStop->removePassenger(pass);
                capturedHumans_++;
                pass.lock()->remove();
            }


            }
    }
}


void MainWindow::keyPressEvent(QKeyEvent *event){


    checkPlayerCollisions();
    int x = 0;
    int y = 0;
    int speed = 5;

    int key = event->key();
    if ( key == Qt::Key_W ) {
        if ( playerGraphics_->y() > -10) {
            y -= speed;
            diry_ = -1;
            dirx_ = 0;
        }
    }
    if ( key == Qt::Key_A ) {
        if (playerGraphics_->x() > 10) {
            x -= speed;
            diry_ = 0;
            dirx_ = -1;
        }
    }
    if ( key == Qt::Key_S ) {
        if (playerGraphics_->y() < map_->height() - 37) {
            y += speed;
            diry_ = 1;
            dirx_ = 0;
        }
    }
    if ( key == Qt::Key_D ) {
        if (playerGraphics_->x() < map_->width() - 22) {
            x += speed;
            diry_ = 0;
            dirx_ = 1;
        }
        }
    playerGraphics_->moveBy(x, y);

}

bool MainWindow::updateGameState(int &i){
    if (capturedHumans_ < 500){
    ui->lcdNumberScore->display(capturedHumans_);
    int seconds = time_->elapsed()/60;
    ui->lcdNumberGameTime->display(seconds);
    return false;
    } else
    {
        int seconds = time_->elapsed()/60;
        ui->lcdNumberScore->display(500);
        i = 500;
        ui->lcdNumberGameTime->display(seconds);

        endGame(seconds);
        return true;
    }
}


void MainWindow::endGame(int score){
    if(!this->game_is_ending) {
        this->game_is_ending = true;
        EndingDialog end(this, score);
        end.exec();
        close();

        }


    }

void MainWindow::setTime(const std::shared_ptr<QElapsedTimer> time)
{
    time_ = time;
}

}

