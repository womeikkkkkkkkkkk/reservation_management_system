#pragma once
#ifndef MANAGERDAO_H
#define MANAGERDAO_H
#include "ManagerDTO.h"
#include <vector>

class ManagerDAO {
public:
    //DAO层的接口--CRUD
    // 根据用户名获取管理员
    ManagerDTO getManagerByUsername(const std::string& username);
    // 获取所有管理员
    std::vector<ManagerDTO> getAllManagers();
    // 插入管理员
    void insertManager(const ManagerDTO& managerDTO);
    // 更新管理员
    void updateManager(const std::string& username, const ManagerDTO& updatedManagerDTO);
    // 删除管理员
    void deleteManager(const std::string& username);
};
#endif
