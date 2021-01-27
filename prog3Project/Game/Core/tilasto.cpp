#include "tilasto.hh"

tilasto::tilasto(){
}

void tilasto::morePassengers(int num)
{
    num++;
}

void tilasto::nysseRemoved()
{
    qDebug() << "Nysse was removed";
}

void tilasto::newNysse()
{
    nyssecount_++;
}

void tilasto::nysseLeft()
{
    nyssecount_--;
}


int tilasto::get_passengers(){
    return totalPassengers;
}
