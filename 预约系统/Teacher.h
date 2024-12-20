#pragma once
#include "Identity.h"
#include "GlobalFile.h"
#include "OutPutMessages.h"
#include "OrderFile.h"
#include <vector>
#include <string>
#include <iostream>
#include "Aes.h"

class Teacher : public Identity // ��ʦ��
{
private:
    int id;

public:
    Teacher();//����
    Teacher(int id, std::string name, std::string passward);//����

    virtual void operMenu();//��д�˵�
    virtual void ReSetName(Identity& person, const std::string name);
    virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward);

    friend std::istream& operator>>(std::istream& is, Teacher& s);//����>>��ʦ

    void SetId(const int& id);//����ID
    void SetName(const std::string& name);//��������
    void SetPassward(const std::string& passward);//��������

    int GetId()const;//��ȡID
    std::string GetName()const;//��ȡ����
    std::string GetPassward()const;//��ȡ����

    void ShowAllOrder();//��ʾ����ԤԼ
    void ValidOrder();//���ԤԼ
};