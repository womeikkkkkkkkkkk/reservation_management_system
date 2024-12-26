#include "TeacherDTO.h"

std::string TeacherDTO::getTeacherName() const {
    return std::string(this->teachername);
}

std::string TeacherDTO::getPassword() const {
    return std::string(this->password);
}

std::string TeacherDTO::getTeacherID() const {
    return std::string(this->teacherID);
}

void TeacherDTO::setTeacherName(const std::string& teachername) {
    this->teachername = teachername;
}

void TeacherDTO::setPassword(const std::string& password) {
    this->password = password;
}

void TeacherDTO::setTeacherID(const std::string& teacherID) {
    this->teacherID = teacherID;
}