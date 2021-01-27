#ifndef PASSENGERGRAPHICS_HH
#define PASSENGERGRAPHICS_HH


#include "../Course/CourseLib/actors/nysse.hh"
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QPainter>
#include <QObject>
#include "../Course/CourseLib/core/location.hh"
#include <QDebug>


const int WIDTHPASS = 5;
const int HEIGHTPASS = 5;


class PassengerGraphics : public QGraphicsItem
{
public:
    /**
     * @brief PassengerGraphics Constructor takes the related passenger as parameter. It also takes the id as
     * an additional parameter.
     * @param related_passenger
     * @param id
     */
    PassengerGraphics(std::shared_ptr<Interface::IActor> related_passenger, int id);
    ~PassengerGraphics();

    /**
     * @brief boundingRect Sets the boundaries for the graphic
     * @return
     */
    QRectF boundingRect() const override;

    /**
     * @brief paint Draws and colors the passenger
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    /**
     * @brief move Makes the single passsenger able to change places, and hides the graphic
     * if the passenger is in bus
     */
    void move();
    int getID();

    std::shared_ptr<Interface::IActor> getRelated_passenger() const;

private:
    QColor color_;
    int x_;
    int y_;
    int id_;
    std::shared_ptr<Interface::IActor> related_passenger_;
};



#endif // PASSENGERGRAPHICS_HH
