#pragma once
#include "Identity.h"
#include "ManagerDTO.h"
#include "ManagerDAO.h"
#include <iostream>

class Manager : public Identity
{
private:
    ManagerDAO* dao;
public:
    Manager(int id, const std::string& name, const std::string& passward, ManagerDAO* dao) : Identity(id, name, passward), dao(dao) {}
    virtual void operMenu()override;
    virtual void reSetName(const std::string& name)override;
    virtual void reSetPassward(const std::string& oldpassward, const std::string& newpassward)override;
    void addManager(const ManagerDTO& managerDTO);
    void removeManager(int id);
    ManagerDTO findManager(int id);
};