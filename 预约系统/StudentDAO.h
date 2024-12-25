#pragma once
#ifndef STUDENTDAO_H
#define STUDENTDAO_H
#include "StudentDTO.h"
#include <vector>

class StudentDAO
{
public:
    //DAO层的接口--CRUD
    // 根据用户名获取学生
    StudentDTO getStudentByUsername(const std::string& username);
    // 获取所有学生
    std::vector<StudentDTO> getAllStudents();
    // 插入学生
    void insertStudent(const StudentDTO& studentDTO);
    // 更新学生
    void updateStudent(const StudentDTO& studentDTO);
    // 删除学生
    void deleteStudent(const StudentDTO& studentDTO);
};
#endif