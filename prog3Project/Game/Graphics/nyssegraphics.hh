#ifndef NYSSEGRAPHICS_HH
#define NYSSEGRAPHICS_HH

#include "../Course/CourseLib/actors/nysse.hh"
#include "QGraphicsItem"
#include <QBrush>
#include <QPainter>
#include <QDebug>

const int WIDTH = 30;
const int HEIGHT = 15;


class NysseGraphics : public QGraphicsItem
{
public:
    /**
     * @brief NysseGraphics Constructor, takes the related objectpointer as an argument.
     * @param the_nysse_we_want
     */
    NysseGraphics(std::shared_ptr<Interface::IActor> the_nysse_we_want);
    ~NysseGraphics();

    /**
     * @brief boundingRect sets the edges for the nysse
     * @return
     */
    QRectF boundingRect() const override;
    

    /**
     * @brief paint Draws and colors each nysse.
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    /**
     * @brief setCoord sets where the graphics are for the nysse
     * @param x
     * @param y
     */
    void setCoord(int x, int y);

    std::shared_ptr<Interface::IActor> related_nysse() const;

private:
    QColor color_;
    int x_;
    int y_;
    std::shared_ptr<Interface::IActor> related_nysse_;
};

#endif // NYSSEGRAPHICS_HH
