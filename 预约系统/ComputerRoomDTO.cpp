#include "ComputerRoomDTO.h"

int ComputerRoomDTO::getId() const
{
    return this->CRID;
}

int ComputerRoomDTO::getMax() const
{
    return this->MAXC;
}

void ComputerRoomDTO::setId(int id)
{
    this->CRID = id;
}

void ComputerRoomDTO::setMax(int max)
{
    this->MAXC = max;
}