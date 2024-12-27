#include "ManagerDAO.h"
#include "ManagerDAO.h"
#include "DatabaseManager.h"
#include "ExceptionLog.h"
#include <vector>
#include <mysql.h>

void ManagerDAO::addManager(const ManagerDTO& manager) {
    std::string managerid = manager.getManagerID();
    std::string managername = manager.getManagerNmae();
    std::string password = manager.getPassword();

    try {
        if (!dbManager.isValidInputs(managerid) || !dbManager.isValidInputs(managername) || !dbManager.isValidInputs(password)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_INSERT_MANAGER;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(3);
            ///managerid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)managerid.c_str();
            binds[0].buffer_length = managerid.length();
            ///managername
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)managername.c_str();
            binds[1].buffer_length = managername.length();
            ///password
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)password.c_str();
            binds[2].buffer_length = password.length();
            ///查询
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_ADD_MANAGER_FALIED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ManagerDAO::deleteManager(const std::string& managerid) {
    try {
        if (!dbManager.isValidInputs(managerid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_DELETE_MANAGER;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)managerid.c_str();
            binds[0].buffer_length = managerid.length();

            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_DELETE_MANAGER_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ManagerDAO::updateManager(const ManagerDTO& manager) {
    std::string managerid = manager.getManagerID();
    std::string managername = manager.getManagerNmae();
    std::string password = manager.getPassword();

    try {
        if (!dbManager.isValidInputs(managerid) || !dbManager.isValidInputs(managername) || !dbManager.isValidInputs(password)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_UPDATE_MANAGER;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(3);
            ///managername
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)managername.c_str();
            binds[0].buffer_length = managername.length();
            ///password
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)password.c_str();
            binds[1].buffer_length = password.length();
            ///managerid
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)managerid.c_str();
            binds[2].buffer_length = managerid.length();

            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_UPDATE_MANAGER_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<ManagerDTO> ManagerDAO::getAllManagers() {
    try {
        std::string query = MYSQL_SELECT_MANAGER_TWICE;
        MYSQL_RES* result = nullptr;
        ///获取结果集
        dbManager.executeQueryWithResult(query, {}, result);
        std::vector<ManagerDTO> managers;
        MYSQL_ROW row;
        ///遍历结果集并转换为DTO
        while ((row = mysql_fetch_row(result))) {
            std::string managerid = row[0] ? row[0] : "";
            std::string managername = row[1] ? row[1] : "";
            std::string password = row[2] ? row[2] : "";
            managers.push_back(ManagerDTO(managerid, managername, password));
        }
        mysql_free_result(result);
        if (!managers.empty()) {
            return managers;
        }
        else {
            throw std::runtime_error(MYSQL_SELECT_MANAGER_ALL_FAILED);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_MANAGER_ALL_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

ManagerDTO ManagerDAO::getManager(const std::string& managerid) {
    try {
        if (!dbManager.isValidInputs(managerid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_SELECT_MANAGER_ONE;
            MYSQL_RES* result = nullptr;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)managerid.c_str();
            binds[0].buffer_length = managerid.length();
            ///获取结果集
            dbManager.executeQueryWithResult(query, binds, result);
            ManagerDTO manager;
            MYSQL_ROW row = nullptr;
            ///结果集转换为DTO
            if ((row = mysql_fetch_row(result))) {
                manager.setManagerID(row[0] ? std::string(row[0]) : "");
                manager.setManagerName(row[1] ? std::string(row[1]) : "");
                manager.setPassword(row[2] ? std::string(row[2]) : "");
            }
            mysql_free_result(result);
            return manager;
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_MANAGER_ONE_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}