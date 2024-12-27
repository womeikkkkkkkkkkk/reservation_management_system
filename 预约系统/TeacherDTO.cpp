#include "TeacherDTO.h"

const std::string& TeacherDTO::getTeacherName() const {
    return std::string(this->teachername);
}

const std::string& TeacherDTO::getPassword() const {
    return std::string(this->password);
}

const std::string& TeacherDTO::getTeacherID() const {
    return std::string(this->teacherid);
}

void TeacherDTO::setTeacherName(const std::string& teachername) {
    this->teachername = teachername;
}

void TeacherDTO::setPassword(const std::string& password) {
    this->password = password;
}

void TeacherDTO::setTeacherID(const std::string& teacherid) {
    this->teacherid = teacherid;
}