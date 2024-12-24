#pragma once
#ifndef COMPUTERROOMMANAGER_H
#define COMPUTERROOMMANAGER_H
#include "ComputerRoomDAO.h"
#include "Identity.h"

class ComputerRoomManager
{
private:
    ComputerRoomDAO crDAO;
public:
    ComputerRoomManager() {}
    bool isManager(const Identity& user);
    void AddComputerRoom(const Identity& user);
    void ShowComputerRoom();
    void GetAllComputerRoom();
    void UpdateComputerRoom(const Identity& user);
    void DeleteComputerRoom(const Identity& user);
};
#endif