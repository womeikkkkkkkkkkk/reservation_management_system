#include "Teacher.h"

bool Teacher::validateCredentials(const std::string& inputUsername, const std::string& inputPassword) {
}

void Teacher::showUserInfo() const {
    std::cout << "Teacher ID: " << this->teacherID << std::endl;
}

std::string Teacher::getTeacherID() const {
    return std::string(this->teacherID);
}