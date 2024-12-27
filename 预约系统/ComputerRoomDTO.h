#pragma once
#ifndef COMPUTERROOMDTO_H
#define COMPUTERROOMDTO_H
#include <iostream>

class ComputerRoomDTO {
private:
    std::string computerroomid;  // 机房编号
    std::string maxcapacity;  // 最大容量

public:
    ComputerRoomDTO() {}
    ComputerRoomDTO(const std::string& id, const  std::string& max) : computerroomid(id), maxcapacity(max) {}

    const std::string& getId() const;
    const std::string& getMax() const;

    void setId(const std::string& id);
    void setMax(const std::string& max);
};
#endif
