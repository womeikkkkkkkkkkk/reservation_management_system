#pragma once
#ifndef REASEVATIONDTO_H
#define RESERVATIONDTO_H
#include "ExceptionLog.h"
#include <string>
#include <unordered_set>

class ReservationDTO {
private:
    std::string reservationid;//预约ID
    std::string userid;//用户ID
    std::string computerroomid;//机房ID
    std::string date;//预约日期
    std::string reservationTime;//预约时段
    std::string status;//预约状态
    std::string createTime;//创建时间
    std::string updateTime;//更新时间

    static const std::unordered_set<std::string> validDays;//有效日期
    static const std::unordered_set<std::string> validTimes;//有效时段
    static const std::unordered_set<std::string> validStatus;//有效状态
public:
    ReservationDTO() {}
    ReservationDTO(const std::string& reservationid, const std::string& userid, const std::string& computerroomid, const std::string& date, const std::string& reservationTime, const std::string& status, const std::string& createTime, const std::string& updateTime) : reservationid(reservationid), userid(userid), computerroomid(computerroomid), date(date), reservationTime(reservationTime), status(status), createTime(createTime), updateTime(updateTime) {}
    //拷贝构造函数
    ReservationDTO(const ReservationDTO& other) : reservationid(other.getReservationID()), userid(other.getUserID()), computerroomid(other.getComputerroomID()), date(other.getDate()), reservationTime(other.getReservationTime()), status(other.getStatus()), createTime(other.getCreateTime()), updateTime(other.getUpdateTime()) {}

    std::string getReservationID() const;
    std::string getUserID() const;
    std::string getComputerroomID() const;
    std::string getDate() const;
    std::string getReservationTime() const;
    std::string getStatus() const;
    std::string getCreateTime() const;
    std::string getUpdateTime() const;

    void setReservationID(const std::string& reservationID);
    void setUserID(const std::string& userID);
    void setComputerroomID(const std::string& computerroomID);
    void setDate(const std::string& date);
    void setReservationTime(const std::string& reservationTime);
    void setStatus(const std::string& status);
    void setCreateTime(const std::string& createTime);
    void setUpdateTime(const std::string& updateTime);

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