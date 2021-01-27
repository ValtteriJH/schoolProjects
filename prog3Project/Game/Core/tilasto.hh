#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "../Course/CourseLib/interfaces/istatistics.hh"
#include "QDebug"

class tilasto : public Interface::IStatistics
{
public:
    tilasto();

    /**
      * @brief Interface has default virtual destructor (base class needs to have a virtual destructor).
      */
     //~IStatistics() override;

    /**
     * @brief morePassengers notifies, that more passangers are added to the game.
     * @param num how many new passangers are added.
     * @pre num > 0
     * @post Exception guarantee: strong
     */
    void morePassengers(int num) override;

    /**
     * @brief nysseRemoved notifies, that the nysse is removed ingame.
     * @pre -
     * @post Exception guarantee: strong
     */
    void nysseRemoved() override;

    /**
     * @brief newNysse notifies, that a new nysse is added to the game.
     * @pre -
     * @post Exception guarantee: strong
     */
    void newNysse() override;

    /**
     * @brief nysseLeft notifies, that a nysse has left the game.
     * @pre -
     * @post Exception guarantee: strong
     */
    void nysseLeft() override;

    int get_passengers();

private:
    int nyssecount_ = 0;
    int totalPassengers = 0;

};

#endif // STATISTICS_HH
