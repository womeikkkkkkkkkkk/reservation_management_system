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

    // ��д��֤�߼�
    bool validateCredentials(const std::string& inputUsername, const std::string& inputPassword) override;
    // ��ʾ��ʦ��Ϣ
    void showUserInfo() const override;
    // ��ȡ��ʦID
    std::string getTeacherID() const;
};

#endif
