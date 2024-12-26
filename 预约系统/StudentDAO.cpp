#include "StudentDAO.h"

StudentDAO::StudentDAO(DatabaseManager& dbMgr) : dbManager(dbMgr) {}

void StudentDAO::addStudent(const StudentDTO& student) {
    std::string studentid = student.getStudentID();
    std::string studentname = student.getStudentName();
    std::string password = student.getPassword();
    try {
        if (!dbManager.isValidInputs(studentname) || !dbManager.isValidInputs(password) || !dbManager.isValidInputs(studentid)) {
            throw::std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = "INSERT INTO students (studentID, studentName, password) VALUES (?, ?, ?)";
            try {
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
            }
            catch (std::exception& e) {
                ExceptionLog::GetInstance()->LogException(MYSQL_ADD_STUDENT_FALIED);
                std::cerr << MYSQL_ADD_STUDENT_FALIED << e.what() << std::endl;
                throw e;
            }
        }
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void StudentDAO::deleteStudent(const std::string& studentID) {
    try {
        if (!dbManager.isValidInputs(studentID)) {
            throw std::runtime_error(ID_NO_EXIST);
        }
        std::string query = "DELETE FROM students WHERE studentID = ?";

        std::vector<MYSQL_BIND> binds(1);
        binds[0].buffer_type = MYSQL_TYPE_STRING;
        binds[0].buffer = (void*)studentID.c_str();
        binds[0].buffer_length = studentID.length();

        dbManager.executeQuery(query, binds);
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
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

        if (!dbManager.isValidInputs(studentname) || dbManager.isValidInputs(password) || dbManager.isValidInputs(studentid)) {
            throw std::runtime_error(MYSQL_INVALID_INPUTS);
        }
        std::string query = "UPDATE students SET studentName = ?, password = ? WHERE studentID = ?";

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
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::vector<StudentDTO> StudentDAO::getAllStudents() {
    try {
        std::string query = "SELECT studentID, studentName, password FROM students";
        MYSQL_RES* result = nullptr;
        ///获取结果集
        dbManager.executeQueryWithResult(query, {}, result);
        std::vector<StudentDTO> students;
        MYSQL_ROW row;
        ///遍历结果集并转换为DTO
        while ((row = mysql_fetch_row(result))) {
            std::string studentID = row[0] ? row[0] : "";
            std::string studentName = row[1] ? row[1] : "";
            std::string password = row[2] ? row[2] : "";
            students.push_back(StudentDTO(studentID, studentName, password));
        }
        mysql_free_result(result);
        return students;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

StudentDTO StudentDAO::getStudent(const std::string& studentID) {
    try {
        if (!dbManager.isValidInputs(studentID)) {
            throw std::runtime_error(ID_NO_EXIST);
        }
        std::string query = "SELECT studentID, studentName, password FROM students WHERE studentID = ?";
        ///绑定参数
        std::vector<MYSQL_BIND> binds(1);
        binds[0].buffer_type = MYSQL_TYPE_STRING;
        binds[0].buffer = (void*)studentID.c_str();
        binds[0].buffer_length = studentID.length();
        MYSQL_RES* result = nullptr;
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
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}