#include "TeacherDAO.h"

void TeacherDAO::addTeacher(const TeacherDTO& teacher) {
    std::string teacherid = teacher.getTeacherID();
    std::string teachername = teacher.getTeacherName();
    std::string password = teacher.getPassword();
    try {
        if (!dbManager.isValidInputs(teachername) || !dbManager.isValidInputs(teacherid) || !dbManager.isValidInputs(password)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_INSERT_TEACHER;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(3);
            ///teacherid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)teacherid.c_str();
            binds[0].buffer_length = teacherid.length();
            ///teachername
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)teachername.c_str();
            binds[1].buffer_length = teachername.length();
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
        std::cerr << MYSQL_ADD_TEACHER_FALIED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void TeacherDAO::deleteTeacher(const std::string& teacherid) {
    try {
        if (!dbManager.isValidInputs(teacherid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_DELETE_TEACHER;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            ///teacherid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)teacherid.c_str();
            binds[0].buffer_length = teacherid.length();

            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_DELETE_TEACHER_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void TeacherDAO::updateTeacher(const TeacherDTO& teacher) {
    try {
        std::string teacherid = teacher.getTeacherID();
        std::string teachername = teacher.getTeacherName();
        std::string password = teacher.getPassword();

        if (!dbManager.isValidInputs(teachername) || !dbManager.isValidInputs(password) || !dbManager.isValidInputs(teacherid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_UPDATE_TEACHER;
            /// 绑定参数
            std::vector<MYSQL_BIND> binds(3);
            /// teacherid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)teacherid.c_str();
            binds[0].buffer_length = teacherid.length();
            /// teachername
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)teachername.c_str();
            binds[1].buffer_length = teachername.length();
            /// password
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)password.c_str();
            binds[2].buffer_length = password.length();
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_UPDATE_TEACHER_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<TeacherDTO> TeacherDAO::getAllTeachers() {
    try {
        std::string query = MYSQL_SELECT_TEACHER_TWICE;
        MYSQL_RES* result = nullptr;
        ///获取结果集
        dbManager.executeQueryWithResult(query, {}, result);
        std::vector<TeacherDTO> teachers;
        MYSQL_ROW row;
        ///遍历结果集并转换为DTO
        while ((row = mysql_fetch_row(result))) {
            std::string teacherid = row[0] ? row[0] : "";
            std::string teachername = row[1] ? row[1] : "";
            std::string password = row[2] ? row[2] : "";
            teachers.push_back(TeacherDTO(teacherid, teachername, password));
        }
        mysql_free_result(result);
        if (!teachers.empty()) {
            return teachers;
        }
        else {
            throw std::runtime_error(MYSQL_SELECT_TEACHER_ALL_FAILED);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_TEACHER_ALL_FAILED << e.what() << std::endl;

        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

TeacherDTO TeacherDAO::getTeacher(const std::string& teacherid) {
    try {
        if (!dbManager.isValidInputs(teacherid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_SELECT_TEACHER_ONE;
            MYSQL_RES* result = nullptr;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)teacherid.c_str();
            binds[0].buffer_length = teacherid.length();
            ///获取结果集
            dbManager.executeQueryWithResult(query, binds, result);
            TeacherDTO teacher;
            MYSQL_ROW row = nullptr;
            ///结果集转换为DTO
            if ((row = mysql_fetch_row(result))) {
                teacher.setTeacherID(row[0] ? std::string(row[0]) : "");
                teacher.setTeacherName(row[1] ? std::string(row[1]) : "");
                teacher.setPassword(row[2] ? std::string(row[2]) : "");
            }
            mysql_free_result(result);
            return teacher;
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_TEACHER_ONE_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}