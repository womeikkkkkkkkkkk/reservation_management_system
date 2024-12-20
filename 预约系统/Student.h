#pragma once
#include "Identity.h"
#include "OutPutMessages.h"
#include "GlobalFile.h"
#include "ComputerRoom.h"
#include "OrderFile.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Aes.h"

class Student : public Identity // ѧ����
{
private:
    int id;

public:
    std::vector<ComputerRoom> vCom;//������

    Student();//����
    Student(int id, std::string name, std::string passward);//����

    virtual void operMenu();//��д�˵�
    virtual void ReSetName(Identity& person, const std::string name);
    virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward);

    friend std::istream& operator>>(std::istream& is, Student& s);//����>>ѧ��

    void SetId(const int& id);//����ID
    void SetName(const std::string& name);//��������
    void SetPassward(const std::string& passward);//��������

    int GetId()const;//��ȡID
    std::string GetName()const;//��ȡ����
    std::string GetPassward()const;//��ȡ����

    void ApplyOrder();   // ����ԤԼ
    void ShowMyOrder();  // �鿴�ҵ�ԤԼ
    void ShowAllOrder(); // �鿴����ԤԼ
    void CancelOrder();  // ȡ��ԤԼ
};