#pragma once
#ifndef MANAGER_H
#define MANAGER_H
#include "Identity.h"
#include <string>
#include <iostream>

class Manager : public Identity {
private:
    std::string username;
    std::string password;
    std::string managerID;

public:
    Manager(const std::string& username, const std::string& password, const std::string& managerID) : username(username), password(password), managerID(managerID) {}

    // 重写验证逻辑
    bool validateCredentials(const std::string& inputUsername, const std::string& inputPassword) override;
    // 显示管理员信息
    void showUserInfo() const override;
    // 获取管理员ID
    std::string getManagerID() const;
};

#endif
