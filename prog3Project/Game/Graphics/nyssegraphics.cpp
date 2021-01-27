#include "nyssegraphics.hh"

NysseGraphics::NysseGraphics(std::shared_ptr<Interface::IActor> the_nysse_we_want):
    x_(the_nysse_we_want->giveLocation().giveX()),
    y_(the_nysse_we_want->giveLocation().giveY()),
    related_nysse_(the_nysse_we_want)
{
    setPos(x_, y_);
}

NysseGraphics::~NysseGraphics()
{

}

QRectF NysseGraphics::boundingRect() const {
    return QRectF(0, -9, WIDTH, HEIGHT+10);
}

void NysseGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    painter->setPen(Qt::black);
    painter->setBrush(Qt::yellow);
    //body
    //std::pair<QStyleOptionGraphicsItem,QWidget> sas = std::make_pair(option, widget); // had to "use" parameters
    painter->drawRoundedRect(QRectF(0, 0, 30, 15), 3, 3);
    //wheels
    painter->setBrush(Qt::black);
    painter->drawEllipse(3,HEIGHT-4, 6, 6);
    painter->drawEllipse(WIDTH-10,HEIGHT-4,6,6);
    //windows
    painter->setPen(Qt::white);
    painter->drawRoundedRect(7, 3, WIDTH-11, 5, 1, 1);
    painter->drawLine(13, 3, 13, 8);
    painter->drawLine(20, 3, 20, 8);
}

void NysseGraphics::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

std::shared_ptr<Interface::IActor> NysseGraphics::related_nysse() const
{
    return related_nysse_;
}
