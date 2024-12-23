#pragma once
#include <string>
#include <iostream>
#include "GlobalFile.h"

class Identity // ��Ա����
{
private:
    std::string name;     // �û���
    std::string passward; // ����
    bool status;//��¼״̬
protected:

public:
    virtual void operMenu() = 0;//�����˵���ڣ���ͨ������if��switchʵ�ֶ༶�˵�

    virtual void ReSetName(Identity& person, const std::string name) = 0;//�޸��û���
    virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) = 0;//�޸�����

    Identity();//Ĭ�Ϲ���
    Identity(int id, std::string name, std::string passward);//����

    void SetName(const std::string& name);//��������
    void SetPasswards(const std::string& passward);//��������

    std::string GetName()const;//��ȡ����
    std::string GetPassward() const;//��ȡ����
};