#pragma once
#ifndef REASEVATIONDTO_H
#define RESERVATIONDTO_H
#include "ExceptionLog.h"
#include <string>
#include <unordered_set>

class ReservationDTO {
private:
    std::string reservationID;//预约ID
    std::string userID;//用户ID
    std::string computerroomID;//机房ID
    std::string date;//预约日期
    int reservationTime;//预约时段
    std::string status;//预约状态
    std::string createTime;//创建时间
    std::string updateTime;//更新时间

    static const std::unordered_set<std::string> validDays;//有效日期
    static const std::unordered_set<int> validTimes;//有效时段
    static const std::unordered_set<std::string> validStatus;//有效状态
public:
    ReservationDTO(const std::string& reservationID, const std::string& userID, const std::string& computerroomID, const std::string& date, const std::string& reservationTime, const std::string& status, const std::string& createTime, const std::string& updateTime) : reservationID(reservationID), userID(userID), computerroomID(computerroomID), date(date), reservationTime(reservationTime), status(status), createTime(createTime), updateTime(updateTime) {}
    //拷贝构造函数
    ReservationDTO(const ReservationDTO& other) : reservationID(other.getReservationID()), userID(other.getUserID()), computerroomID(other.getComputerroomID()), date(other.getDate()), reservationTime(other.getReservationTime()), status(other.getStatus()), createTime(other.getCreateTime()), updateTime(other.getUpdateTime()) {}

    std::string getReservationID() const;
    std::string getUserID() const;
    std::string getComputerroomID() const;
    std::string getDate() const;
    int getReservationTime() const;
    std::string getStatus() const;
    std::string getCreateTime() const;
    std::string getUpdateTime() const;

    void setReservationID(std::string reservationID);
    void setUserID(std::string userID);
    void setComputerroomID(std::string computerroomID);
    void setDate(std::string date);
    void setReservationTime(int reservationTime);
    void setStatus(std::string status);
    void setCreateTime(std::string createTime);
    void setUpdateTime(std::string updateTime);

    bool validDate() const;
    bool validTime() const;
    bool validStatu() const;
    bool validCreateTime() const;
    bool validUpdateTime() const;
    std::string toString() const;

    ReservationDTO& operator=(const ReservationDTO& other);
    bool operator==(const ReservationDTO& other) const;
    bool operator!=(const ReservationDTO& other) const;
    bool operator<(const ReservationDTO& other) const;
    bool operator>(const ReservationDTO& other) const;
    bool operator<=(const ReservationDTO& other) const;
    bool operator>=(const ReservationDTO& other) const;
};
#endif