#include "TeacherDTO.h"

std::string TeacherDTO::getTeacherName() const
{
    return std::string(this->teachername);
}

std::string TeacherDTO::getPassword() const
{
    return std::string(this->password);
}

std::string TeacherDTO::getTeacherID() const
{
    return std::string(this->teacherID);
}

void TeacherDTO::setTeacherName(std::string teachername)
{
    this->teachername = teachername;
}

void TeacherDTO::setPassword(std::string password)
{
    this->password = password;
}

void TeacherDTO::setTeacherID(std::string teacherID)
{
    this->teacherID = teacherID;
}