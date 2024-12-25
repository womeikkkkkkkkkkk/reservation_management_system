#include "StudentDAO.h"

void StudentDAO::addStudent(const StudentDTO& student) {
    std::string studentid = student.getStudentID();
    std::string studentname = student.getStudentName();
    std::string password = student.getPassword();
    try {
        if (!sqlProtection.isValidInput(studentname) || !sqlProtection.isValidInput(password) || !sqlProtection.isValidInput(studentid)) {
            throw::std::runtime_error(POTENTIAL_SQL_INJECTION_DETECTED);
        }
        else {
            std::string query = "INSERT INTO students (studentID, studentName, password) VALUES (?, ?, ?)";
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
}

void StudentDAO::updateStudent(const StudentDTO& student) {
}

std::vector<StudentDTO> StudentDAO::getAllStudents() {
}

StudentDTO StudentDAO::getStudent(const std::string& studentID) {
}