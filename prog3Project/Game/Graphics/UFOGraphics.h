#ifndef TEEKKARIGRAPHICS_H
#define TEEKKARIGRAPHICS_H

#include "Actors/teekkari.h"

#include <QBrush>
#include <QPainter>
#include <QGraphicsItem>

namespace Junttarit {

class UFOGraphics : public QGraphicsItem
{
public:
    /**
     * @brief UFOGraphics Plasyer graphics constructor.
     * @param x
     * @param y
     * @param relatedGraphic_
     */
    UFOGraphics(int x, int y, std::shared_ptr<Junttarit::Teekkari> relatedGraphic_);
    virtual ~UFOGraphics();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //QPainterPath shape() const;
    void updatePos();

protected:
    void advance(int step);

private:
    int x_;
    int y_;
    qreal angle_ = 30;
    std::shared_ptr<Junttarit::Teekkari> relatedGraphic_;
};

}

#endif // TEEKKARIGRAPHICS_H
