#pragma once
#ifndef COMPUTERROOMDTO_H
#define COMPUTERROOMDTO_H
#include <iostream>

class ComputerRoomDTO {
private:
    int CRID;  // �������
    int MAXC;  // �������

public:
    ComputerRoomDTO(int id = 0, int max = 0) : CRID(id), MAXC(max) {}

    int getId() const;
    int getMax() const;

    void getId(int id);
    void getMax(int max);

    // ���ڴ�ӡ������Ϣ
    friend std::ostream& operator<<(std::ostream& os, const ComputerRoomDTO& cr);
};
#endif
