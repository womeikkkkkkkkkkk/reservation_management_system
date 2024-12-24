#pragma once
#ifndef IDENTITY_H
#define IDENTITY_H
#include <string>
#include <iostream>
#include "GlobalFile.h"

class Identity //�����֤
{
public:
    //�����֤�ӿ�
    virtual bool validateCredentials(const std::string& username, const std::string& password) = 0;
    //��ȡ�û���Ϣ
    virtual void showUserInfo()const = 0;
    //�˳���¼
    virtual void logout() const {
        std::cout << LOGOUT_SUCCESS << std::endl;
    }
};
#endif