#pragma once
#ifndef TEACHERDAO_H
#define TEACHERDAO_H
#include "TeacherDTO.h"
#include <vector>

class TeacherDAO {
public:
    //DAO层提供CRUD接口
    // 添加教师
    void addTeacher(const TeacherDTO& teacher);
    // 删除教师
    void deleteTeacher(const std::string& teacherID);
    // 更新教师
    void updateTeacher(const TeacherDTO& teacher);
    // 获取所有教师
    std::vector<TeacherDTO> getAllTeachers();
    // 获取教师
    TeacherDTO getTeacher(const std::string& teacherID);
};
#endif