#include "ComputerRoomDTO.h"

const std::string& ComputerRoomDTO::getId() const {
    return this->computerroomid;
}

const std::string& ComputerRoomDTO::getMax() const {
    return this->maxcapacity;
}

void ComputerRoomDTO::setId(const std::string& id) {
    this->computerroomid = id;
}

void ComputerRoomDTO::setMax(const std::string& max) {
    this->maxcapacity = max;
}