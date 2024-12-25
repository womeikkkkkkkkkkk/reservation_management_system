#pragma once
#ifndef MANAGERDAO_H
#define MANAGERDAO_H
#include "ManagerDTO.h"
#include <vector>

class ManagerDAO {
public:
    //DAO层提供CRUD接口
    // 添加管理员
    void addManager(const ManagerDTO& manager);
    // 删除管理员
    void deleteManager(const std::string& managerID);
    // 更新管理员
    void updateManager(const ManagerDTO& manager);
    // 获取所有管理员
    std::vector<ManagerDTO> getAllManagers();
    // 获取管理员
    ManagerDTO getManager(const std::string& managerID);
};
#endif
