#pragma once
#include <string>
#include "GlobalFile.h"

class Identity // ��Ա����
{
protected:
    int id;
    std::string name;     // �û���
    std::string passward; // ����
    bool status;//��¼״̬

public:
    Identity() : id(NULLID), status(false) {}
    Identity(int id, const std::string& name, const std::string& passward) : id(id), name(name), passward(passward), status(false) {}

    virtual void operMenu() = 0;//�����˵���ڣ���ͨ������if��switchʵ�ֶ༶�˵�

    virtual void reSetName(const std::string& name) = 0;//�޸��û���
    virtual void reSetPassward(const std::string& oldpassward, const std::string& newpassward) = 0;//�޸�����

    void setName(const std::string& name);//��������
    void setPassward(const std::string& passward);//��������
    void setStatus(bool status);
    int getId() const;//
    std::string getName()const;//��ȡ����
    std::string getPassward() const;//��ȡ����
    bool getStatus()const;
};