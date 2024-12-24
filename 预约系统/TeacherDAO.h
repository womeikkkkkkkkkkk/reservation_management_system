#pragma once
#ifndef TEACHERDAO_H
#define TEACHERDAO_H
#include "TeacherDTO.h"
#include <vector>
class TeacherDAO
{
private:

public:
    //DAO²ãµÄ½Ó¿Ú--CRUD
    TeacherDTO getTeacherByUsername(const std::string& username);
    std::vector<TeacherDTO> getAllTeachers();
    void insertTeacher(const TeacherDTO& teacherDTO);
    void updateTeacher(const TeacherDTO& teacherDTO);
    void deleteTeacher(const TeacherDTO& teacherDTO);
};
#endif