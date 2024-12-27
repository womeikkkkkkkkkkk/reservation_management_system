#pragma once
#ifndef MANAGERDTO_H
#define MANAGERDTO_H
#include <string>
class ManagerDTO {
private:
    std::string managername;
    std::string password;
    std::string managerid;
public:
    ManagerDTO() {}
    ManagerDTO(const std::string& managername, const std::string& password, const std::string& managerid) : managername(managername), password(password), managerid(managerid) {}

    const std::string& getManagerNmae() const;
    const std::string& getPassword() const;
    const std::string& getManagerID() const;

    void setManagerName(const std::string& managername);
    void setPassword(const std::string& password);
    void setManagerID(const std::string& managerid);
};
#endif
