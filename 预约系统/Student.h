#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include "Identity.h"
#include "StudentDAO.h"
#include <string>
#include <iostream>

class Student : public Identity {
private:
    std::string studentname;
    std::string password;
    std::string studentid;
    StudentDAO& studentDAO;
public:
    Student(const std::string& studentname, const std::string& password, const std::string& studentid) : studentname(studentname), password(password), studentid(studentid) {}

    // 重写验证逻辑
    bool validateCredentials(const std::string& inputStudentname, const std::string& inputPassword) override;
    // 显示学生信息
    void showUserInfo() const override;
    // 获取学生ID
    std::string getStudentID() const;
};

#endif
