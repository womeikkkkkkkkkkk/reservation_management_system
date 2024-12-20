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

class Manager : public Identity // 管理员类
{
private:
    int id;

public:
    std::vector<Student> vStu;//学生表
    std::vector<Teacher> vTea;//教师表
    std::vector<ComputerRoom> vCom;//机房表

    Manager();//构造
    Manager(std::string name, std::string passward);//构造

    virtual void operMenu();//重写菜单
    virtual void ReSetName(Identity& person, const std::string name);
    virtual void ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward);

    friend std::istream& operator>>(std::istream& is, Manager& s);//重载>>管理员，用于读写数据

    bool TextIdCmp(int fid, std::string text);

    void SetId(const int& id);//设置ID
    void SetName(const std::string& name);//设置名字
    void SetPassward(const std::string& passward);//设置密码

    int GetId()const;//获取ID
    std::string GetName()const;//获取名字
    std::string GetPassward()const;//获取密码

    void InitVector();//载入数据
    bool CheckRepeat(const int id, const int type);//去重

    void AddPerson();//添加用户
    void RemovePerson(const std::string& name);//删除用户（待实现）
    void FindPerson(int select, const std::string& name);//查找用户(待实现)
    void ShowPerson();//显示所有用户
    void ShowComputer();//显示机房信息
    void CleanFile();//清空数据
};