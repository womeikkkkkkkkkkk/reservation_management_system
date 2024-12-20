#pragma once
#include "GlobalFile.h"
#include <iostream>

class ComputerRoom {
private:
    int CRID;//机房编号
    int MAXC;//最大容量
public:
    ComputerRoom();
    void SetId(int id);//设置ID
    void SetMax(int max);//设置最大容量
    int GetId()const;//获取ID
    int GetMax()const;//获取最大容量
    friend std::istream& operator>>(std::istream& is, ComputerRoom& s);//重载>>机房，用于读写数据
};