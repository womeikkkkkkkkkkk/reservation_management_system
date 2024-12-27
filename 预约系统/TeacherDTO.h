#pragma once
#ifndef TEACHERDTO_H
#define TEACHERDTO_H
#include <string>

class TeacherDTO {
private:
    std::string teachername;
    std::string password;
    std::string teacherid;
public:
    TeacherDTO() {}
    TeacherDTO(const std::string& teachername, const std::string& password, const std::string teacherid) : teachername(teachername), password(password), teacherid(teacherid) {}

    const std::string& getTeacherName() const;
    const std::string& getPassword() const;
    const std::string& getTeacherID() const;

    void setTeacherName(const std::string& teachername);
    void setPassword(const std::string& password);
    void setTeacherID(const std::string& teacherid);
};
#endif