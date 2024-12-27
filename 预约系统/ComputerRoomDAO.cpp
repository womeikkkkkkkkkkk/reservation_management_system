#include "ComputerRoomDAO.h"
/*
int computerroomid;  // 机房编号
int maxcapacity;  // 最大容量
*/
void ComputerRoomDAO::addComputerRoom(const ComputerRoomDTO& computerRoom) {
    try {
        std::string computerroomid = computerRoom.getId();
        std::string maxcapacity = computerRoom.getMax();

        if (!dbManager.isValidInputs(computerroomid) || !dbManager.isValidInputs(maxcapacity)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_INSERT_COMPUTERROOM;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(2);
            ///computerroomid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)computerroomid.c_str();
            binds[0].buffer_length = computerroomid.length();
            ///maxcapacity
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)maxcapacity.c_str();
            binds[0].buffer_length = maxcapacity.length();
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_ADD_COMPUTER_FALIED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ComputerRoomDAO::deleteComputerRoom(const std::string& computerroomid) {
    try {
        if (!dbManager.isValidInputs(computerroomid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_DELETE_RESERVATION;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            ///computerroomid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)computerroomid.c_str();
            binds[0].buffer_length = computerroomid.length();
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_DELETE_COMPUTER_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ComputerRoomDAO::updateComputerRoom(const ComputerRoomDTO& computerRoom) {
    try {
        std::string computerroomid = computerRoom.getId();
        std::string maxcapacity = computerRoom.getMax();
        if (!dbManager.isValidInputs(computerroomid) || !dbManager.isValidInputs(maxcapacity)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_UPDATE_COMPUTERROOM;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(2);
            ///computerroomid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)computerroomid.c_str();
            binds[0].buffer_length = computerroomid.length();
            ///maxcapacity
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)maxcapacity.c_str();
            binds[0].buffer_length = maxcapacity.length();
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

std::vector<ComputerRoomDTO> ComputerRoomDAO::getAllComputerRooms() {
    try {
        std::string query = MYSQL_SELECT_COMPUTERROOM_TWICE;
        MYSQL_RES* result = nullptr;
        ///获取结果集
        dbManager.executeQueryWithResult(query, {}, result);
        std::vector<ComputerRoomDTO> computerrooms;
        MYSQL_ROW row;
        ///遍历结果集并转换为DTO
        while ((row = mysql_fetch_row(result))) {
            std::string computerroomid = row[0] ? row[0] : "";
            std::string maxcapacity = row[1] ? row[1] : "";
            computerrooms.push_back(ComputerRoomDTO(computerroomid, maxcapacity));
        }
        mysql_free_result(result);
        if (!computerrooms.empty()) {
            return computerrooms;
        }
        else {
            throw std::runtime_error(MYSQL_SELECT_COMPUTER_ALL_FAILED);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_COMPUTER_ALL_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

ComputerRoomDTO ComputerRoomDAO::getComputerRoom(const std::string& computerroomid) {
    try {
        if (!dbManager.isValidInputs(computerroomid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_SELECT_COMPUTERROOM_TWICE;
            MYSQL_RES* result = nullptr;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)computerroomid.c_str();
            binds[0].buffer_length = computerroomid.length();
            ///获取结果集
            dbManager.executeQueryWithResult(query, binds, result);
            ComputerRoomDTO computerrooms;
            MYSQL_ROW row = nullptr;
            ///结果集转换为DTO
            if ((row = mysql_fetch_row(result))) {
                computerrooms.setId(row[0] ? std::string(row[0]) : "");
                computerrooms.setMax(row[1] ? std::string(row[1]) : "");
            }
            mysql_free_result(result);
            return computerrooms;
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