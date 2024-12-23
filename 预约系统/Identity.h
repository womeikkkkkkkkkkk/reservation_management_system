#pragma once
#include <string>
#include "GlobalFile.h"

class Identity // 人员基类
{
protected:
    int id;
    std::string name;     // 用户名
    std::string passward; // 密码
    bool status;//登录状态

public:
    Identity() : id(NULLID), status(false) {}
    Identity(int id, const std::string& name, const std::string& passward) : id(id), name(name), passward(passward), status(false) {}

    virtual void operMenu() = 0;//二级菜单入口，可通过叠加if，switch实现多级菜单

    virtual void reSetName(const std::string& name) = 0;//修改用户名
    virtual void reSetPassward(const std::string& oldpassward, const std::string& newpassward) = 0;//修改密码

    void setName(const std::string& name);//设置名字
    void setPassward(const std::string& passward);//设置密码
    void setStatus(bool status);
    int getId() const;//
    std::string getName()const;//获取名字
    std::string getPassward() const;//获取密码
    bool getStatus()const;
};