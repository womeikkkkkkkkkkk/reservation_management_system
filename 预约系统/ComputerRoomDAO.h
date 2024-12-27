#pragma once
#ifndef COMPUTERROOMDAO_H
#define COMPUTERROOMDAO_H
#include "ComputerRoomDTO.h"
#include "DatabaseManager.h"
#include "ExceptionLog.h"
#include <vector>
#include <mysql.h>

class ComputerRoomDAO {
private:
    DatabaseManager& dbManager;
public:
    ComputerRoomDAO(DatabaseManager dbMgr) : dbManager(dbMgr) {}

    //DAO层提供CRUD接口
    // 添加机房
    void addComputerRoom(const ComputerRoomDTO& computerRoom);
    // 删除机房
    void deleteComputerRoom(const std::string& computerroomid);
    // 更新机房
    void updateComputerRoom(const ComputerRoomDTO& computerRoom);
    // 获取所有机房
    std::vector<ComputerRoomDTO> getAllComputerRooms();
    // 获取机房
    ComputerRoomDTO getComputerRoom(const std::string& computerroomid);
};
#endif
