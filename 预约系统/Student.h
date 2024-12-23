#pragma once
#include "Identity.h"
#include "StudentDAO.h"
#include "StudentDTO.h"
#include <iostream>

class Student :public Identity
{
private:
    StudentDAO* dao;
public:
    Student(int id, const std::string& name, const std::string& password, StudentDAO* dao) : Identity(id, name, password), dao(dao) {}
    virtual void operMenu() override;
    virtual void reSetName(const std::string& name) override;
    virtual void reSetPassward(const std::string& oldPassward, const std::string& newPassward) override;
}
;