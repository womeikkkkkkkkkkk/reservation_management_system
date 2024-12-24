#pragma once
#ifndef COMPUTERROOMDTO_H
#define COMPUTERROOMDTO_H
#include <iostream>

class ComputerRoomDTO {
private:
    int CRID;  // 机房编号
    int MAXC;  // 最大容量

public:
    ComputerRoomDTO(int id = 0, int max = 0) : CRID(id), MAXC(max) {}

    int getId() const;
    int getMax() const;

    void getId(int id);
    void getMax(int max);

    // 用于打印机房信息
    friend std::ostream& operator<<(std::ostream& os, const ComputerRoomDTO& cr);
};
#endif
