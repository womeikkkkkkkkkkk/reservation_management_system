#pragma once
#ifndef STUDENTDTO_H
#define STUDENTDTO_H
#include <string>

class StudentDTO {
private:
    std::string studentname;
    std::string password;
    std::string studentID;
public:
    StudentDTO() {}
    StudentDTO(const std::string& username, const std::string& password, const std::string& studentID) : studentname(username), password(password), studentID(studentID) {}

    std::string getStudentName() const;
    std::string getPassword() const;
    std::string getStudentID() const;

    void setStudentName(const std::string& studentname);
    void setPassword(const std::string& password);
    void setStudentID(const std::string& studentID);
};
#endif
