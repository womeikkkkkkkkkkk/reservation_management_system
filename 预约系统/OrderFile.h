#pragma once
#include <map>
#include <string>
#include <fstream>
#include "GlobalFile.h"
#include <iostream>

class OrderFile//ԤԼ��
{
private:
    int OrderSize;//������

public:
    std::map<int, std::map<std::string, std::string>> OrderData;//������

    OrderFile();//����

    int const GetSize();//��ȡ������
    void UpdateOrder();//���±�
};