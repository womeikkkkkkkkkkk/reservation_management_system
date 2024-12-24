#pragma once
#ifndef TEACHERDTO_H
#define TEACHERDTO_H
#include <string>

class TeacherDTO
{
public:
    std::string teachername;
    std::string password;
    std::string teacherID;

    TeacherDTO(const std::string& username, const std::string& password, const std::string teacherID) : teachername(username), password(password), teacherID(teacherID) {}

    std::string getTeacherName() const;
    std::string getPassword() const;
    std::string getStudentID() const;
    void setStudentName(std::string studentname);
    void setPassword(std::string password);
    void setStudentID(std::string studentID);
};
#endif