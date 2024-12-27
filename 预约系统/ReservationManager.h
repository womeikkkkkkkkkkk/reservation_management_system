#pragma once
#ifndef RESERVATIONMANAGER_H
#define RESERVATIONMANAGER_H
#include "ReservationDAO.h"
#include <exception>
///提供预约管理API接口
class ReservationManager {
private:
    ReservationDAO reservationDAO;
public:
    ReservationManager(DatabaseManager& dbManager) : reservationDAO(dbManager) {}

    void addReservation(const ReservationDTO& reservation);
    void deleteReservation(const std::string& reservationid);
    void updateReservation(const ReservationDTO& reservation);
    std::vector<ReservationDTO> getAllReservations();
    ReservationDTO getReservation(const std::string& reservationid);
};
#endif