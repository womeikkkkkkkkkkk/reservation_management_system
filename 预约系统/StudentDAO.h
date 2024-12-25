#pragma once
#ifndef STUDENTDAO_H
#define STUDENTDAO_H
#include "StudentDTO.h"
#include <vector>

class StudentDAO {
public:
    //DAO层提供CRUD接口
    // 添加学生
    void addStudent(const StudentDTO& student);
    // 删除学生
    void deleteStudent(const std::string& studentID);
    // 更新学生
    void updateStudent(const StudentDTO& student);
    // 获取所有学生
    std::vector<StudentDTO> getAllStudents();
    // 获取学生
    StudentDTO getStudent(const std::string& studentID);
};
#endif