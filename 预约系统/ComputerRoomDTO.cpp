#include "ComputerRoomDTO.h"

const int& ComputerRoomDTO::getId() const {
    return this->CRID;
}

const int& ComputerRoomDTO::getMax() const {
    return this->MAXC;
}

void ComputerRoomDTO::setId(const int& id) {
    this->CRID = id;
}

void ComputerRoomDTO::setMax(const int& max) {
    this->MAXC = max;
}