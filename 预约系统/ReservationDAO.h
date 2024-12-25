#pragma once
#ifndef RESERVATIONDAO_H
#define RESERVATIONDAO_H
#include "ReservationDTO.h"
#include <vector>

class ReservationDAO {
public:
    //DAO层提供CRUD接口
    // 添加预约
    void addReservation(const ReservationDTO& reservation);
    // 删除预约
    void deleteReservation(const std::string& reservationID);
    // 更新预约
    void updateReservation(const ReservationDTO& reservation);
    // 获取所有预约
    std::vector<ReservationDTO> getAllReservations();
    // 获取预约
    ReservationDTO getReservation(const std::string& reservationID);
};
#endif