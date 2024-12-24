#pragma once
#ifndef COMPUTERROOMDAO_H
#define COMPUTERROOMDAO_H
#include "ComputerRoomDTO.h"
#include <vector>
class ComputerRoomDAO
{
public:
    // �����ݿ⣨���ļ��������������
    void InsertComputerRoom(const ComputerRoomDTO& cr);
    // ��ȡָ��ID�Ļ���
    ComputerRoomDTO GetComputerRoomById(int id);
    // ���»�����Ϣ
    void UpdateComputerRoom(int id, const ComputerRoomDTO& updatedCR);
    // ɾ������
    void DeleteComputerRoom(int id);
    // ��ȡ���л�����Ϣ
    std::vector<ComputerRoomDTO> GetAllComputerRooms();
};
#endif
