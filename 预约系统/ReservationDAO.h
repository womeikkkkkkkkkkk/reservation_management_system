#pragma once
#ifndef RESERVATIONDAO_H
#define RESERVATIONDAO_H
#include "ReservationDTO.h"
#include "DatabaseManager.h"
#include "ExceptionLog.h"
#include <vector>
#include <mysql.h>

class ReservationDAO {
private:
    DatabaseManager& dbManager;
public:
    ReservationDAO(DatabaseManager dbMgr) : dbManager(dbMgr) {}

    //DAO层提供CRUD接口
    // 添加预约
    void addReservation(const ReservationDTO& reservation);
    // 删除预约
    void deleteReservation(const std::string& reservationid);
    // 更新预约
    void updateReservation(const ReservationDTO& reservation);
    // 获取所有预约
    std::vector<ReservationDTO> getAllReservations();
    // 获取预约
    ReservationDTO getReservation(const std::string& reservationid);
};
#endif