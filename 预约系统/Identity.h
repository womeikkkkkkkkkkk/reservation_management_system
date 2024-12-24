#pragma once
#ifndef IDENTITY_H
#define IDENTITY_H
#include <string>
#include <iostream>
#include "GlobalFile.h"

class Identity //身份验证
{
public:
    //身份验证接口
    virtual bool validateCredentials(const std::string& username, const std::string& password) = 0;
    //获取用户信息
    virtual void showUserInfo()const = 0;
    //退出登录
    virtual void logout() const {
        std::cout << LOGOUT_SUCCESS << std::endl;
    }
};
#endif