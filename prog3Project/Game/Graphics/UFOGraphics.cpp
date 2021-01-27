#include "UFOGraphics.h"

namespace Junttarit{
Junttarit::UFOGraphics::UFOGraphics(int x, int y, std::shared_ptr<Junttarit::Teekkari> relatedTeekkari) :
        x_(x),
        y_(y),
        relatedGraphic_(relatedTeekkari)
    {
        setPos(mapToParent(x_ % 100, y_ % 100));
        setRotation(angle_);
    }


Junttarit::UFOGraphics::~UFOGraphics()
{

}

QRectF Junttarit::UFOGraphics::boundingRect() const
{
    return QRectF(1, 1, 32, 32);
}

void Junttarit::UFOGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    QColor color(128, 0, 128);
    QBrush brush(color);
    painter->setPen(Qt::black);
    painter->setBrush(brush);
    //body
    painter->drawEllipse(2, 2, 30, 30);
    //glass
    painter->setBrush(Qt::red);
    QRectF rect = QRectF(10, 10, 15, 15);
    painter->drawEllipse(rect);

}

void Junttarit::UFOGraphics::updatePos()
{
    x_ = relatedGraphic_->giveLocation().giveX();
    y_ = relatedGraphic_->giveLocation().giveY();
    setPos(mapToParent(x_ % 100, y_ % 100));
}

void Junttarit::UFOGraphics::advance(int step)
{
    if (!step)
        return;
    angle_ += 30;
    if (angle_ > 360) {
        angle_ -= 360;
    }
    setRotation(angle_);
}
}
