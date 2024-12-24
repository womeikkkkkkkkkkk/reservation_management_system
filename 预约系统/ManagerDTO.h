#pragma once
#ifndef MANAGERDTO_H
#define MANAGERDTO_H
#include <string>
class ManagerDTO
{
public:
    std::string managername;
    std::string password;
    std::string managerID;

    ManagerDTO(const std::string& username, const std::string& password, const std::string& managerID) : managername(username), password(password), managerID(managerID) {}
};
#endif
