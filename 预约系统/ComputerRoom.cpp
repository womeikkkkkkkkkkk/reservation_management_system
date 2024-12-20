#pragma once
#include "ComputerRoom.h"

ComputerRoom::ComputerRoom() {
    this->CRID = NULLID; this->MAXC = NULLCONTAINER;
}

void ComputerRoom::SetId(int id) {
    this->CRID = id;
}

void ComputerRoom::SetMax(int max) {
    this->MAXC = max;
}

int ComputerRoom::GetId()const {
    return this->CRID;
}

int ComputerRoom::GetMax()const {
    return this->MAXC;
}

std::istream& operator>>(std::istream& is, ComputerRoom& s) {
    int id;
    int max;
    is >> id;
    is >> max;
    s.SetId(id);
    s.SetMax(max);
    return is;
}