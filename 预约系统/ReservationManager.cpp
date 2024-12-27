#include "ReservationManager.h"

void ReservationManager::addReservation(const ReservationDTO& reservation) {
    try {
        if (!reservation.validDate()) {
            throw std::invalid_argument("无效的预约日期");
        }
        if (!reservation.validTime()) {
            throw std::invalid_argument("无效的预约时段");
        }
        if (!reservation.validStatu()) {
            throw std::invalid_argument("无效的预约状态");
        }
        if (!reservation.validCreateTime()) {
            throw std::invalid_argument("无效的创建时间");
        }
        if (!reservation.validUpdateTime()) {
            throw std::invalid_argument("无效的更新时间");
        }
        reservationDAO.addReservation(reservation);
        std::cout << "预约 " << reservation.getReservationID() << " 添加成功" << std::endl;
    }
    catch (const std::exception& e) {
        std::string s = "添加预约失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ReservationManager::deleteReservation(const std::string& reservationid) {
    try {
        if (reservationid.empty()) {
            throw std::invalid_argument("预约ID不能为空");
        }
        reservationDAO.deleteReservation(reservationid);
        std::cout << "预约 " << reservationid << " 删除成功" << std::endl;
    }
    catch (const std::exception& e) {
        std::string s = "删除预约失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ReservationManager::updateReservation(const ReservationDTO& reservation) {
    try {
        if (!reservation.validDate()) {
            throw std::invalid_argument("无效的预约日期");
        }
        if (!reservation.validTime()) {
            throw std::invalid_argument("无效的预约时段");
        }
        if (!reservation.validStatu()) {
            throw std::invalid_argument("无效的预约状态");
        }
        if (!reservation.validCreateTime()) {
            throw std::invalid_argument("无效的创建时间");
        }
        if (!reservation.validUpdateTime()) {
            throw std::invalid_argument("无效的更新时间");
        }
        reservationDAO.updateReservation(reservation);
        std::cout << "预约 " << reservation.getReservationID() << " 更新成功" << std::endl;
    }
    catch (const std::exception& e) {
        std::string s = "更新预约失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<ReservationDTO> ReservationManager::getAllReservations() {
    try {
        return reservationDAO.getAllReservations();
    }
    catch (const std::exception& e) {
        std::string s = "获取所有预约失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

ReservationDTO ReservationManager::getReservation(const std::string& reservationid) {
    try {
        if (reservationid.empty()) {
            throw std::invalid_argument("预约ID不能为空");
        }

        return reservationDAO.getReservation(reservationid);
    }
    catch (const std::exception& e) {
        std::string s = "获取预约失败: " + std::string(e.what());
        std::cerr << s << std::endl;
        ExceptionLog::GetInstance()->LogException(s);
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}