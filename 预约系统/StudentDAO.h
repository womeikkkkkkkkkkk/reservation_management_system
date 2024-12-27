#pragma once
#ifndef STUDENTDAO_H
#define STUDENTDAO_H
#include "StudentDTO.h"
#include "ExceptionLog.h"
#include "DatabaseManager.h"
#include <vector>
#include <mysql.h>

class StudentDAO {
private:
    DatabaseManager& dbManager;
public:
    StudentDAO(DatabaseManager& dbMgr) : dbManager(dbMgr) {}

    //DAO层提供CRUD接口
    // 添加学生
    void addStudent(const StudentDTO& student);
    // 删除学生
    void deleteStudent(const std::string& studentid);
    // 更新学生
    void updateStudent(const StudentDTO& student);
    // 获取所有学生
    std::vector<StudentDTO> getAllStudents();
    // 获取学生
    StudentDTO getStudent(const std::string& studentid);
};
#endif