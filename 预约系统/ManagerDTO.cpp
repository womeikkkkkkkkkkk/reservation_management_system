#include "ManagerDTO.h"

std::string ManagerDTO::getManagerNmae() const {
    return std::string(this->managername);
}

std::string ManagerDTO::getPassword() const {
    return std::string(this->password);
}

std::string ManagerDTO::geetManagerID() const {
    return std::string(this->managerID);
}

void ManagerDTO::setManagerName(const std::string& managername) {
    this->managername = managername;
}

void ManagerDTO::setPassword(const std::string& password) {
    this->password = password;
}

void ManagerDTO::setManagerID(const std::string& managerID) {
    this->managerID = managerID;
}