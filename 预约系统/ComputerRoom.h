#pragma once
#include "GlobalFile.h"
#include <iostream>

class ComputerRoom {
private:
    int CRID;//�������
    int MAXC;//�������
public:
    ComputerRoom();
    void SetId(int id);//����ID
    void SetMax(int max);//�����������
    int GetId()const;//��ȡID
    int GetMax()const;//��ȡ�������
    friend std::istream& operator>>(std::istream& is, ComputerRoom& s);//����>>���������ڶ�д����
};