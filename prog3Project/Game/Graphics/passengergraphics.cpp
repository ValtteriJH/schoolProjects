#include "passengergraphics.hh"

PassengerGraphics::PassengerGraphics(std::shared_ptr<Interface::IActor> related_passenger, int id): QGraphicsItem(),
    x_(related_passenger->giveLocation().giveX()),
    y_(related_passenger->giveLocation().giveY()),
    id_(id),
    related_passenger_(related_passenger)

{

}

PassengerGraphics::~PassengerGraphics(){
    qDebug() << "I have been removed";
}

QRectF PassengerGraphics::boundingRect() const {
    return QRectF(x_, y_, WIDTHPASS + 5, HEIGHTPASS + 5);
}


void PassengerGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    //QBrush(color_);
    painter->setPen(Qt::black);
    // Sign
    painter->setBrush(Qt::black);
    painter->drawEllipse(x_, y_, WIDTHPASS, HEIGHTPASS);

}
int PassengerGraphics::getID()
{
    return id_;
}

std::shared_ptr<Interface::IActor> PassengerGraphics::getRelated_passenger() const
{
    return related_passenger_;
}
void PassengerGraphics::move(){
    std::shared_ptr<CourseSide::Passenger> pass = std::dynamic_pointer_cast<CourseSide::Passenger>(related_passenger_);
    if(pass->isInVehicle()){
        prepareGeometryChange();
        this->hide();

    }else{
        Interface::Location new_loc = pass->getStop()->getLocation();
        x_ = new_loc.giveX();
        y_ = new_loc.giveY();
        this->show();
    }

}
