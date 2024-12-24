#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include "Identity.h"
#include <string>
#include <iostream>

class Student : public Identity {
private:
    std::string username;
    std::string password;
    std::string studentID;

public:
    Student(const std::string& username, const std::string& password, const std::string& studentID) : username(username), password(password), studentID(studentID) {}

    // 重写验证逻辑
    bool validateCredentials(const std::string& inputUsername, const std::string& inputPassword) override;
    // 显示学生信息
    void showUserInfo() const override;
    // 获取学生ID
    std::string getStudentID() const;
};

#endif
