#pragma once
#ifndef TEACHERDAO_H
#define TEACHERDAO_H
#include "TeacherDTO.h"
#include <vector>

class TeacherDAO
{
public:
    //DAO层的接口--CRUD
    // 根据用户名获取教师
    TeacherDTO getTeacherByUsername(const std::string& username);
    // 获取所有教师
    std::vector<TeacherDTO> getAllTeachers();
    // 插入教师
    void insertTeacher(const TeacherDTO& teacherDTO);
    // 更新教师
    void updateTeacher(const TeacherDTO& teacherDTO);
    // 删除教师
    void deleteTeacher(const TeacherDTO& teacherDTO);
};
#endif