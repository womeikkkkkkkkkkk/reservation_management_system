#pragma once
#ifndef COMPUTERROOMMANAGER_H
#define COMPUTERROOMMANAGER_H
#include "ComputerRoomDAO.h"
#include "Identity.h"
#include <exception>
///提供机房管理API接口
class ComputerRoomManager {
private:
    ComputerRoomDAO computerroomDAO;
public:
    ComputerRoomManager(DatabaseManager& dbManager) : computerroomDAO(dbManager) {}

    void addComputerRoom(const ComputerRoomDTO& computerRoom);
    void deleteComputerRoom(const std::string& computerroomid);
    void updateComputerRoom(const ComputerRoomDTO& computerRoom);
    std::vector<ComputerRoomDTO> getAllComputerRooms();
    ComputerRoomDTO getComputerRoom(const std::string& computerroomid);
};
#endif
