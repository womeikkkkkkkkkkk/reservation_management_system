#pragma once
#ifndef COMPUTERROOMDAO_H
#define COMPUTERROOMDAO_H
#include "ComputerRoomDTO.h"
#include <vector>
class ComputerRoomDAO
{
public:
    // 获取指定ID的机房
    ComputerRoomDTO GetComputerRoomById(int id);
    // 获取所有机房信息
    std::vector<ComputerRoomDTO> GetAllComputerRooms();
    // 插入机房数据
    void InsertComputerRoom(const ComputerRoomDTO& cr);
    // 更新机房信息
    void UpdateComputerRoom(int id, const ComputerRoomDTO& updatedCR);
    // 删除机房
    void DeleteComputerRoom(int id);
};
#endif
