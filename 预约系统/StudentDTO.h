#pragma once
#ifndef STUDENTDTO_H
#define STUDENTDTO_H
#include <string>

class StudentDTO {
public:
    std::string studentname;
    std::string password;
    std::string studentID;

    StudentDTO(const std::string& username, const std::string& password, const std::string& studentID) : studentname(username), password(password), studentID(studentID) {}

    std::string getStudentName() const;
    std::string getPassword() const;
    std::string getStudentID() const;
    void setStudentName(std::string studentname);
    void setPassword(std::string password);
    void setStudentID(std::string studentID);
};
#endif
