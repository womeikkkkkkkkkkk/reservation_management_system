#include "ManagerDTO.h"

const std::string& ManagerDTO::getManagerNmae() const {
    return std::string(this->managername);
}

const std::string& ManagerDTO::getPassword() const {
    return std::string(this->password);
}

const std::string& ManagerDTO::geetManagerID() const {
    return std::string(this->managerid);
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