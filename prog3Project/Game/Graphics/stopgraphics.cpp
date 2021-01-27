#include "stopgraphics.hh"

StopGraphics::StopGraphics(std::shared_ptr<Interface::IStop> the_stop_we_want): QGraphicsItem(),
    x_(the_stop_we_want->getLocation().giveX()),
    y_(the_stop_we_want->getLocation().giveY()),
    related_stop_(the_stop_we_want)
{
}

StopGraphics::~StopGraphics(){

}

QRectF StopGraphics::boundingRect() const {
    return QRectF(x_, y_, WIDTHSTOP + 10, HEIGHTSTOP + 10);
}


void StopGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    //QBrush(color_);
    painter->setPen(Qt::black);
    // Sign
    painter->setBrush(Qt::red);
    painter->drawEllipse(x_, y_, WIDTHSTOP, HEIGHTSTOP);
    //Text
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    QFont font = painter->font();
    font.setPixelSize(5);
    painter->setFont(font);
    const QRect rect = QRect(x_ + 2, y_ + 5, 20, 50);
    painter->drawText(rect, "STOP");
    if ( related_stop_->getPassengers().size() != 0){
        painter->setPen(Qt::black);
        painter->setBrush(Qt::black);
        painter->drawEllipse(x_, y_, 2, 2);
    }
}

std::shared_ptr<Interface::IStop> StopGraphics::related_stop() const
{
    return related_stop_;
}
