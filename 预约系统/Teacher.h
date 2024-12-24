#pragma once
#ifndef TEACHER_H
#define TEACHER_H
#include "Identity.h"
#include <string>
#include <iostream>

class Teacher : public Identity {
private:
    std::string username;
    std::string password;
    std::string teacherID;

public:
    Teacher(const std::string& username, const std::string& password, const std::string& teacherID) : username(username), password(password), teacherID(teacherID) {}

    // 重写验证逻辑
    bool validateCredentials(const std::string& inputUsername, const std::string& inputPassword) override;
    // 显示教师信息
    void showUserInfo() const override;
    // 获取教师ID
    std::string getTeacherID() const;
};

#endif
