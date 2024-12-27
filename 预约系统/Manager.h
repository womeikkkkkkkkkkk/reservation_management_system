#pragma once
#ifndef MANAGER_H
#define MANAGER_H
#include "Identity.h"
#include <string>
#include <iostream>

class Manager : public Identity {
private:
    std::string managername;
    std::string password;
    std::string managerid;

public:
    Manager(const std::string& managername, const std::string& password, const std::string& managerid) : managername(managername), password(password), managerid(managerid) {}

    // 重写验证逻辑
    bool validateCredentials(const std::string& inputManagername, const std::string& inputPassword) override;
    // 显示管理员信息
    void showUserInfo() const override;
    // 获取管理员ID
    std::string getManagerID() const;
};

#endif
