#pragma once
#include "Identity.h"
#include "GlobalFile.h"
#include "OutPutMessages.h"
#include "ComputerRoom.h"
#include "Student.h"
#include "Teacher.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Aes.h"

class Manager : public Identity // ����Ա��
{
private:
    int id;

public:
    std::vector<Student> vStu;//ѧ����
    std::vector<Teacher> vTea;//��ʦ��
    std::vector<ComputerRoom> vCom;//������

    Manager();//����
    Manager(std::string name, std::string passward);//����

    virtual void operMenu();//��д�˵�
    virtual void ReSetName(Identity& person, const std::string name);
    virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward);

    friend std::istream& operator>>(std::istream& is, Manager& s);//����>>����Ա�����ڶ�д����

    bool TextIdCmp(int fid, std::string text);

    void SetId(const int& id);//����ID
    void SetName(const std::string& name);//��������
    void SetPassward(const std::string& passward);//��������

    int GetId()const;//��ȡID
    std::string GetName()const;//��ȡ����
    std::string GetPassward()const;//��ȡ����

    void InitVector();//��������
    bool CheckRepeat(const int id, const int type);//ȥ��

    void AddPerson();//����û�
    void RemovePerson(const std::string& name);//ɾ���û�����ʵ�֣�
    void FindPerson(int select, const std::string& name);//�����û�(��ʵ��)
    void ShowPerson();//��ʾ�����û�
    void ShowComputer();//��ʾ������Ϣ
    void CleanFile();//�������
};