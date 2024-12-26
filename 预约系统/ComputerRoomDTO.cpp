#include "ComputerRoomDTO.h"

int ComputerRoomDTO::getId() const {
    return this->CRID;
}

int ComputerRoomDTO::getMax() const {
    return this->MAXC;
}

void ComputerRoomDTO::setId(const int& id) {
    this->CRID = id;
}

void ComputerRoomDTO::setMax(const int& max) {
    this->MAXC = max;
}