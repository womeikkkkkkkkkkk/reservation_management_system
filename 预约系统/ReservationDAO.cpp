#include "ReservationDAO.h"

void ReservationDAO::addReservation(const ReservationDTO& reservation) {
    try {
        std::string reservationid = reservation.getReservationID();
        std::string userid = reservation.getUserID();
        std::string computerroomid = reservation.getComputerroomID();
        std::string date = reservation.getDate();
        std::string reservationtime = reservation.getReservationTime();
        std::string status = reservation.getStatus();
        std::string createtime = reservation.getCreateTime();
        std::string updatetime = reservation.getUpdateTime();

        if (!dbManager.isValidInputs(reservationid) || !dbManager.isValidInputs(userid) || !dbManager.isValidInputs(computerroomid) || !dbManager.isValidInputs(date) || !dbManager.isValidInputs(reservationtime) || !dbManager.isValidInputs(status) || !dbManager.isValidInputs(createtime) || !dbManager.isValidInputs(updatetime)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_UPDATE_RESERVATION;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(8);
            ///reservationid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)reservationid.c_str();
            binds[0].buffer_length = reservationid.length();
            ///userid
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)reservationid.c_str();
            binds[1].buffer_length = userid.length();
            ///computerroomid
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)reservationid.c_str();
            binds[2].buffer_length = computerroomid.length();
            ///date
            binds[3].buffer_type = MYSQL_TYPE_STRING;
            binds[3].buffer = (void*)reservationid.c_str();
            binds[3].buffer_length = date.length();
            ///reservationtime
            binds[4].buffer_type = MYSQL_TYPE_STRING;
            binds[4].buffer = (void*)reservationid.c_str();
            binds[4].buffer_length = reservationtime.length();
            ///status
            binds[5].buffer_type = MYSQL_TYPE_STRING;
            binds[5].buffer = (void*)reservationid.c_str();
            binds[5].buffer_length = status.length();
            ///createtime
            binds[6].buffer_type = MYSQL_TYPE_STRING;
            binds[6].buffer = (void*)reservationid.c_str();
            binds[6].buffer_length = createtime.length();
            ///updatetime
            binds[7].buffer_type = MYSQL_TYPE_STRING;
            binds[7].buffer = (void*)reservationid.c_str();
            binds[7].buffer_length = updatetime.length();
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_ADD_RESERVATION_FALIED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ReservationDAO::deleteReservation(const std::string& reservationid) {
    try {
        if (!dbManager.isValidInputs(reservationid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_DELETE_RESERVATION;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            ///reservationid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)reservationid.c_str();
            binds[0].buffer_length = reservationid.length();
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_DELETE_RESERVATION_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ReservationDAO::updateReservation(const ReservationDTO& reservation) {
    try {
        std::string reservationid = reservation.getReservationID();
        std::string userid = reservation.getUserID();
        std::string computerroomid = reservation.getComputerroomID();
        std::string date = reservation.getDate();
        std::string reservationtime = reservation.getReservationTime();
        std::string status = reservation.getStatus();
        std::string createtime = reservation.getCreateTime();
        std::string updatetime = reservation.getUpdateTime();

        if (!dbManager.isValidInputs(reservationid) || !dbManager.isValidInputs(userid) || !dbManager.isValidInputs(computerroomid) || !dbManager.isValidInputs(date) || !dbManager.isValidInputs(reservationtime) || !dbManager.isValidInputs(status) || !dbManager.isValidInputs(createtime) || !dbManager.isValidInputs(updatetime)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_UPDATE_RESERVATION;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(8);
            ///reservationid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)reservationid.c_str();
            binds[0].buffer_length = reservationid.length();
            ///userid
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)reservationid.c_str();
            binds[1].buffer_length = userid.length();
            ///computerroomid
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)reservationid.c_str();
            binds[2].buffer_length = computerroomid.length();
            ///date
            binds[3].buffer_type = MYSQL_TYPE_STRING;
            binds[3].buffer = (void*)reservationid.c_str();
            binds[3].buffer_length = date.length();
            ///reservationtime
            binds[4].buffer_type = MYSQL_TYPE_STRING;
            binds[4].buffer = (void*)reservationid.c_str();
            binds[4].buffer_length = reservationtime.length();
            ///status
            binds[5].buffer_type = MYSQL_TYPE_STRING;
            binds[5].buffer = (void*)reservationid.c_str();
            binds[5].buffer_length = status.length();
            ///createtime
            binds[6].buffer_type = MYSQL_TYPE_STRING;
            binds[6].buffer = (void*)reservationid.c_str();
            binds[6].buffer_length = createtime.length();
            ///updatetime
            binds[7].buffer_type = MYSQL_TYPE_STRING;
            binds[7].buffer = (void*)reservationid.c_str();
            binds[7].buffer_length = updatetime.length();
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_UPDATE_RESERVATION_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<ReservationDTO> ReservationDAO::getAllReservations() {
    try {
        std::string query = MYSQL_SELECT_RESERVATION_TWICE;
        MYSQL_RES* result = nullptr;
        ///获取结果集
        dbManager.executeQueryWithResult(query, {}, result);
        std::vector<ReservationDTO> reservations;
        MYSQL_ROW row;
        ///遍历结果集并转换为DTO
        while ((row = mysql_fetch_row(result))) {
            std::string reservationid = row[0] ? row[0] : "";
            std::string userid = row[1] ? row[1] : "";
            std::string computerroomid = row[2] ? row[2] : "";
            std::string date = row[3] ? row[3] : "";
            std::string reservationtime = row[4] ? row[4] : "";
            std::string status = row[5] ? row[5] : "";
            std::string createtime = row[6] ? row[6] : "";
            std::string updatetime = row[7] ? row[7] : "";
            reservations.push_back(ReservationDTO(reservationid, userid, computerroomid, date, reservationtime, status, createtime, updatetime));
        }
        mysql_free_result(result);
        if (!reservations.empty()) {
            return reservations;
        }
        else {
            throw std::runtime_error(MYSQL_SELECT_RESERVATION_ALL_FAILED);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_RESERVATION_ALL_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

ReservationDTO ReservationDAO::getReservation(const std::string& reservationid) {
    try {
        if (!dbManager.isValidInputs(reservationid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_SELECT_RESERVATION_ONE;
            MYSQL_RES* result = nullptr;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)reservationid.c_str();
            binds[0].buffer_length = reservationid.length();
            ///获取结果集
            dbManager.executeQueryWithResult(query, binds, result);
            ReservationDTO reservations;
            MYSQL_ROW row = nullptr;
            ///结果集转换为DTO
            if ((row = mysql_fetch_row(result))) {
                reservations.setReservationID(row[0] ? std::string(row[0]) : "");
                reservations.setUserID(row[1] ? std::string(row[1]) : "");
                reservations.setComputerroomID(row[2] ? std::string(row[2]) : "");
                reservations.setDate(row[3] ? std::string(row[3]) : "");
                reservations.setReservationTime(row[4] ? std::string(row[4]) : "");
                reservations.setStatus(row[5] ? std::string(row[5]) : "");
                reservations.setCreateTime(row[6] ? std::string(row[6]) : "");
                reservations.setUpdateTime(row[7] ? std::string(row[7]) : "");
            }
            mysql_free_result(result);
            return reservations;
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_RESERVATION_ONE_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}