#include "StudentDAO.h"

void StudentDAO::addStudent(const StudentDTO& student) {
    std::string studentid = student.getStudentID();
    std::string studentname = student.getStudentName();
    std::string password = student.getPassword();
    try {
        if (!dbManager.isValidInputs(studentname) || !dbManager.isValidInputs(password) || !dbManager.isValidInputs(studentid)) {
            throw::std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_INSERT_STUDENT;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(3);
            /// studentid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)studentid.c_str();
            binds[0].buffer_length = studentid.length();
            ///studentname
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)studentname.c_str();
            binds[1].buffer_length = studentname.length();
            /// password
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)password.c_str();
            binds[2].buffer_length = password.length();
            ///查询
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(MYSQL_ADD_STUDENT_FALIED);
        std::cerr << MYSQL_ADD_STUDENT_FALIED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void StudentDAO::deleteStudent(const std::string& studentid) {
    try {
        if (!dbManager.isValidInputs(studentid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_DELETE_STUDENT;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            ///studentid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)studentid.c_str();
            binds[0].buffer_length = studentid.length();

            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_DELETE_STUDENT_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void StudentDAO::updateStudent(const StudentDTO& student) {
    try {
        std::string studentid = student.getStudentID();
        std::string studentname = student.getStudentName();
        std::string password = student.getPassword();

        if (!dbManager.isValidInputs(studentname) || !dbManager.isValidInputs(password) || !dbManager.isValidInputs(studentid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_UPDATE_STUDENT;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(3);
            /// studentid
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)studentid.c_str();
            binds[0].buffer_length = studentid.length();
            ///studentname
            binds[1].buffer_type = MYSQL_TYPE_STRING;
            binds[1].buffer = (void*)studentname.c_str();
            binds[1].buffer_length = studentname.length();
            /// password
            binds[2].buffer_type = MYSQL_TYPE_STRING;
            binds[2].buffer = (void*)password.c_str();
            binds[2].buffer_length = password.length();
            dbManager.executeQuery(query, binds);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_UPDATE_STUDENT_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<StudentDTO> StudentDAO::getAllStudents() {
    try {
        std::string query = MYSQL_SELECT_STUDENT_TWICE;
        MYSQL_RES* result = nullptr;
        ///获取结果集
        dbManager.executeQueryWithResult(query, {}, result);
        std::vector<StudentDTO> students;
        MYSQL_ROW row;
        ///遍历结果集并转换为DTO
        while ((row = mysql_fetch_row(result))) {
            std::string studentid = row[0] ? row[0] : "";
            std::string studentname = row[1] ? row[1] : "";
            std::string password = row[2] ? row[2] : "";
            students.push_back(StudentDTO(studentid, studentname, password));
        }
        mysql_free_result(result);
        if (!students.empty()) {
            return students;
        }
        else {
            throw std::runtime_error(MYSQL_SELECT_STUDENT_ALL_FAILED);
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_STUDENT_ALL_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

StudentDTO StudentDAO::getStudent(const std::string& studentid) {
    try {
        if (!dbManager.isValidInputs(studentid)) {
            throw std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = MYSQL_SELECT_STUDENT_ONE;
            MYSQL_RES* result = nullptr;
            ///绑定参数
            std::vector<MYSQL_BIND> binds(1);
            binds[0].buffer_type = MYSQL_TYPE_STRING;
            binds[0].buffer = (void*)studentid.c_str();
            binds[0].buffer_length = studentid.length();
            ///获取结果集
            dbManager.executeQueryWithResult(query, binds, result);
            StudentDTO student;
            MYSQL_ROW row = nullptr;
            ///结果集转换为DTO
            if ((row = mysql_fetch_row(result))) {
                student.setStudentID(row[0] ? std::string(row[0]) : "");
                student.setStudentName(row[1] ? std::string(row[1]) : "");
                student.setPassword(row[2] ? std::string(row[2]) : "");
            }
            mysql_free_result(result);
            return student;
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        std::cerr << MYSQL_SELECT_STUDENT_ONE_FAILED << e.what() << std::endl;
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}