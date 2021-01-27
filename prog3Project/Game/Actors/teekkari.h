#ifndef TEEKKARI_H
#define TEEKKARI_H

#include "interfaces/iactor.hh"
#include "core/location.hh"

namespace Junttarit
{

class Teekkari : public Interface::IActor
{
public:
    Teekkari(int x, int y);

    Interface::Location giveLocation() const;
    void move(Interface::Location loc);
    bool isRemoved() const;
    void remove();

private:
    Interface::Location location_;
    bool removed_;

};

}

#endif // TEEKKARI_H
