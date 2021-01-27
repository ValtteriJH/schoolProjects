#ifndef STOPGRAPHICS_HH
#define STOPGRAPHICS_HH

#include "../Course/CourseLib/actors/nysse.hh"
#include <QGraphicsItem>
#include <QBrush>
#include <QPainter>
#include <QObject>


const int WIDTHSTOP = 15;
const int HEIGHTSTOP = 15;


class StopGraphics : public QGraphicsItem
{
public:
    /**
     * @brief StopGraphics Constructor takes the corresponding stop and makes graphics.
     * @param the_stop_we_want
     */
    StopGraphics(std::shared_ptr<Interface::IStop> the_stop_we_want);
    ~StopGraphics();

    QRectF boundingRect() const override;
    /**
     * @brief paint draws and colors the stop
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    /**
     * @brief setCoord set the coordinates for the stop.
     * @param x
     * @param y
     */
    void setCoord(int x, int y);

    std::shared_ptr<Interface::IStop> related_stop() const;


private:
    QColor color_;
    int x_;
    int y_;
    std::shared_ptr<Interface::IStop> related_stop_;
};

#endif // STOPGRAPHICS_HH
