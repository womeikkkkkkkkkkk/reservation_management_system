#pragma once
#ifndef MANAGERDTO_H
#define MANAGERDTO_H
#include <string>
class ManagerDTO
{
private:
    std::string managername;
    std::string password;
    std::string managerID;
public:

    ManagerDTO(const std::string& username, const std::string& password, const std::string& managerID) : managername(username), password(password), managerID(managerID) {}

    std::string getManagerNmae() const;
    std::string getPassword() const;
    std::string geetManagerID() const;

    void setManagerName(const std::string& managername);
    void setPassword(const std::string& password);
    void setManagerID(const std::string& managerID);
};
#endif
