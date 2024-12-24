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

    // ��д��֤�߼�
    bool validateCredentials(const std::string& inputUsername, const std::string& inputPassword) override;
    // ��ʾ����Ա��Ϣ
    void showUserInfo() const override;
    // ��ȡ����ԱID
    std::string getManagerID() const;
};

#endif
