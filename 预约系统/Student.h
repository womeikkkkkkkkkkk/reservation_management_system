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

    // ��д��֤�߼�
    bool validateCredentials(const std::string& inputUsername, const std::string& inputPassword) override;
    // ��ʾѧ����Ϣ
    void showUserInfo() const override;
    // ��ȡѧ��ID
    std::string getStudentID() const;
};

#endif
