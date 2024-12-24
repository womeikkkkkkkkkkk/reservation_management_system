#pragma once
#ifndef STUDENTDAO_H
#define STUDENTDAO_H
#include "StudentDTO.h"
#include <vector>

class StudentDAO
{
private:

public:
    //DAO²ãµÄ½Ó¿Ú--CRUD
    StudentDTO getStudentByUsername(const std::string& username);
    std::vector<StudentDTO> getAllStudents();
    void insertStudent(const StudentDTO& studentDTO);
    void updateStudent(const StudentDTO& studentDTO);
    void deleteStudent(const StudentDTO& studentDTO);
};
#endif