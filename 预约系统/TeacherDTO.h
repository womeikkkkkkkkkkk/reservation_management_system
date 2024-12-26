#pragma once
#ifndef TEACHERDTO_H
#define TEACHERDTO_H
#include <string>

class TeacherDTO {
private:
    std::string teachername;
    std::string password;
    std::string teacherID;
public:

    TeacherDTO(const std::string& username, const std::string& password, const std::string teacherID) : teachername(username), password(password), teacherID(teacherID) {}

    std::string getTeacherName() const;
    std::string getPassword() const;
    std::string getTeacherID() const;

    void setTeacherName(const std::string& teachername);
    void setPassword(const std::string& password);
    void setTeacherID(const std::string& teacherID);
};
#endif