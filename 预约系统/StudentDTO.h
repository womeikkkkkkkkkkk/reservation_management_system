#pragma once
#ifndef STUDENTDTO_H
#define STUDENTDTO_H
#include <string>

class StudentDTO {
private:
    std::string studentname;
    std::string password;
    std::string studentid;
public:
    StudentDTO() {}
    StudentDTO(const std::string& username, const std::string& password, const std::string& studentid) : studentname(username), password(password), studentid(studentid) {}

    const std::string& getStudentName() const;
    const std::string& getPassword() const;
    const std::string& getStudentID() const;

    void setStudentName(const std::string& studentname);
    void setPassword(const std::string& password);
    void setStudentID(const std::string& studentid);
};
#endif
