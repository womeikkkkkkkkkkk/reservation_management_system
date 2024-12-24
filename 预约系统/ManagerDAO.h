#pragma once
#ifndef MANAGERDAO_H
#define MANAGERDAO_H
#include "ManagerDTO.h"
#include <vector>

class ManagerDAO {
private:

public:
    //DAO²ãµÄ½Ó¿Ú--CRUD
    ManagerDTO getManagerByUsername(const std::string& username);
    std::vector<StudentDTO> getAllManagers();
    void insertManager(const ManagerDTO& managerDTO);
    void updateManager(const std::string& username, const ManagerDTO& updatedManagerDTO);
    void deleteManager(const std::string& username);
};
#endif
