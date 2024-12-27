#include "Teacher.h"

bool Teacher::validateCredentials(const std::string& inputTeachername, const std::string& inputPassword) {
}

void Teacher::showUserInfo() const {
    std::cout << "Teacher ID: " << this->teacherid << std::endl;
}

std::string Teacher::getTeacherID() const {
    return std::string(this->teacherid);
}