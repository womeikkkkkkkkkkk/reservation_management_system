#include "StudentDTO.h"

std::string StudentDTO::getStudentName() const {
    return std::string(this->studentname);
}

std::string StudentDTO::getPassword() const {
    return std::string(this->password);
}

std::string StudentDTO::getStudentID() const {
    return std::string(this->studentID);
}

void StudentDTO::setStudentName(const std::string& studentname) {
    this->studentname = studentname;
}

void StudentDTO::setPassword(const std::string& password) {
    this->password = password;
}

void StudentDTO::setStudentID(const std::string& studentID) {
    this->studentID = studentID;
}