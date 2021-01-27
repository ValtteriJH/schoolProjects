#include "teekkari.h"

namespace Junttarit
{


Teekkari::Teekkari(int x, int y) : location_(Interface::Location(x, y))
{

}

Interface::Location Teekkari::giveLocation() const
{
    return location_;
}

void Teekkari::move(Interface::Location loc)
{
    location_ = loc;
}

bool Teekkari::isRemoved() const
{
    return removed_;
}

void Teekkari::remove()
{
    removed_ = true;
}

}
