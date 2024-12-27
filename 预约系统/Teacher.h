#pragma once
#ifndef TEACHER_H
#define TEACHER_H
#include "Identity.h"
#include "TeacherDAO.h"
#include <string>
#include <iostream>

class Teacher : public Identity {
private:
    std::string teachername;
    std::string password;
    std::string teacherid;
    TeacherDAO& teacherDAO;
public:
    Teacher(const std::string& teachername, const std::string& password, const std::string& teacherid) : teachername(teachername), password(password), teacherid(teacherid) {}

    // 重写验证逻辑
    bool validateCredentials(const std::string& inputTeacherid, const std::string& inputPassword) override;
    // 显示教师信息
    void showUserInfo() const override;
    // 获取教师ID
    std::string getTeacherID() const;
};

#endif
