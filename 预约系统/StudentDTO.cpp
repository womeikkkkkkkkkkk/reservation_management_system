#include "StudentDTO.h"

const std::string& StudentDTO::getStudentName() const {
    return std::string(this->studentname);
}

const std::string& StudentDTO::getPassword() const {
    return std::string(this->password);
}

const std::string& StudentDTO::getStudentID() const {
    return std::string(this->studentid);
}

void StudentDTO::setStudentName(const std::string& studentname) {
    this->studentname = studentname;
}

void StudentDTO::setPassword(const std::string& password) {
    this->password = password;
}

void StudentDTO::setStudentID(const std::string& studentid) {
    this->studentid = studentid;
}