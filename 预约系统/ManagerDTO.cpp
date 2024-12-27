#include "ManagerDTO.h"

const std::string& ManagerDTO::getManagerNmae() const {
    return this->managername;
}

const std::string& ManagerDTO::getPassword() const {
    return this->password;
}

const std::string& ManagerDTO::getManagerID() const {
    return this->managerid;
}

void ManagerDTO::setManagerName(const std::string& managername) {
    this->managername = managername;
}

void ManagerDTO::setPassword(const std::string& password) {
    this->password = password;
}

void ManagerDTO::setManagerID(const std::string& managerid) {
    this->managerid = managerid;
}