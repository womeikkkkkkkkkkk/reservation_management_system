#include "ReservationDTO.h"

const std::unordered_set<std::string> ReservationDTO::validDays = { "Monday","Tuesday","Wednesday","Thursday", " Friday" };
const std::unordered_set<int> ReservationDTO::validTimes = { 1,2,3,4,5,6,7,8,9,10 };
const std::unordered_set<std::string> ReservationDTO::validStatus = { "valid","invalid" };

ReservationDTO& ReservationDTO::operator=(const ReservationDTO& other) {
    if (this != &other) {
        reservationID = other.getReservationID();
        userID = other.getUserID();
        computerroomID = other.getComputerroomID();
        date = other.getDate();
        reservationTime = other.getReservationTime();
        status = other.getStatus();
        createTime = other.getCreateTime();
        updateTime = other.getUpdateTime();
    }
    return *this;
}

bool ReservationDTO::operator==(const ReservationDTO& other) const {
    return reservationID == other.getReservationID() &&
        userID == other.getUserID() &&
        computerroomID == other.getComputerroomID() &&
        date == other.getDate() &&
        reservationTime == other.getReservationTime() &&
        status == other.getStatus() &&
        createTime == other.getCreateTime() &&
        updateTime == other.getUpdateTime();
}

bool ReservationDTO::operator!=(const ReservationDTO& other) const {
    return !(*this == other);
}

bool ReservationDTO::operator<(const ReservationDTO& other) const {
    if (reservationID < other.getReservationID()) {
        return true;
    }
    if (reservationID > other.getReservationID()) {
        return false;
    }

    if (userID < other.getUserID()) {
        return true;
    }
    if (userID > other.getUserID()) {
        return false;
    }

    if (computerroomID < other.getComputerroomID()) {
        return true;
    }
    if (computerroomID > other.getComputerroomID()) {
        return false;
    }

    if (date < other.getDate()) {
        return true;
    }
    if (date > other.getDate()) {
        return false;
    }

    if (reservationTime < other.getReservationTime()) {
        return true;
    }
    if (reservationTime > other.getReservationTime()) {
        return false;
    }

    if (status < other.getStatus()) {
        return true;
    }
    if (status > other.getStatus()) {
        return false;
    }

    if (createTime < other.getCreateTime()) {
        return true;
    }
    if (createTime > other.getCreateTime()) {
        return false;
    }

    if (updateTime < other.getUpdateTime()) {
        return true;
    }
    if (updateTime > other.getUpdateTime()) {
        return false;
    }

    return false;
}

bool ReservationDTO::operator>(const ReservationDTO& other) const {
    if (reservationID > other.getReservationID()) {
        return true;
    }
    if (reservationID < other.getReservationID()) {
        return false;
    }

    if (userID > other.getUserID()) {
        return true;
    }
    if (userID < other.getUserID()) {
        return false;
    }

    if (computerroomID > other.getComputerroomID()) {
        return true;
    }
    if (computerroomID < other.getComputerroomID()) {
        return false;
    }

    if (date > other.getDate()) {
        return true;
    }
    if (date < other.getDate()) {
        return false;
    }

    if (reservationTime > other.getReservationTime()) {
        return true;
    }
    if (reservationTime < other.getReservationTime()) {
        return false;
    }

    if (status > other.getStatus()) {
        return true;
    }
    if (status < other.getStatus()) {
        return false;
    }

    if (createTime > other.getCreateTime()) {
        return true;
    }
    if (createTime < other.getCreateTime()) {
        return false;
    }

    if (updateTime > other.getUpdateTime()) {
        return true;
    }
    if (updateTime < other.getUpdateTime()) {
        return false;
    }

    return false;
}

bool ReservationDTO::operator<=(const ReservationDTO& other) const {
    return !(*this > other);//!(a>b) == a<=b
}

bool ReservationDTO::operator>=(const ReservationDTO& other) const {
    return !(*this < other);//!(a<b) == a>=b
}

std::string ReservationDTO::getReservationID() const {
    return std::string(this->reservationID);
}

std::string ReservationDTO::getUserID() const {
    return std::string(this->userID);
}

std::string ReservationDTO::getComputerroomID() const {
    return std::string(this->computerroomID);
}

std::string ReservationDTO::getDate() const {
    return std::string(this->date);
}

int ReservationDTO::getReservationTime() const {
    return int(this->reservationTime);
}

std::string ReservationDTO::getStatus() const {
    return std::string(this->status);
}

std::string ReservationDTO::getCreateTime() const {
    return std::string(this->createTime);
}

std::string ReservationDTO::getUpdateTime() const {
    return std::string(this->updateTime);
}

void ReservationDTO::setReservationID(const std::string& reservationID) {
    this->reservationID = reservationID;
}

void ReservationDTO::setUserID(const std::string& userID) {
    this->userID = userID;
}

void ReservationDTO::setComputerroomID(const std::string& computerroomID) {
    this->computerroomID = computerroomID;
}

void ReservationDTO::setDate(const std::string& date) {
    try {
        if (date.empty()) {
            throw std::invalid_argument(DATE_ERROR);
        }
        this->date = date;
        if (!validDate()) {
            throw std::invalid_argument(DATE_ERROR);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}
void ReservationDTO::setReservationTime(const int& reservationTime) {
    try {
        if (reservationID.empty()) {
            throw std::invalid_argument(TIME_ERROR);
        }
        this->reservationTime = reservationTime;
        if (!validTime()) {
            throw std::invalid_argument(TIME_ERROR);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ReservationDTO::setStatus(const std::string& status) {
    try {
        if (status.empty()) {
            throw std::invalid_argument(STATUS_ERROR);
        }
        this->status = status;
        if (!validStatu()) {
            throw std::invalid_argument(STATUS_ERROR);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

void ReservationDTO::setCreateTime(const std::string& createTime) {
    try {
        if (createTime.empty()) {
            throw std::invalid_argument(TIME_ERROR);
        }
        this->createTime = createTime;
        if (!validCreateTime()) {
            throw std::invalid_argument(TIME_ERROR);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}
void ReservationDTO::setUpdateTime(const std::string& updateTime) {
    try {
        if (updateTime.empty()) {
            throw std::invalid_argument(TIME_ERROR);
        }
        this->updateTime = updateTime;
        if (!validUpdateTime()) {
            throw std::invalid_argument(TIME_ERROR);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}
bool ReservationDTO::validDate() const {
    try {
        if (date.empty()) {
            throw std::invalid_argument(DATE_ERROR);
        }
        else {
            return validDays.find(date) != validDays.end();
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
    return false;
}

bool ReservationDTO::validTime() const {
    try {
        if (date.empty()) {
            throw std::invalid_argument(DATE_ERROR);
        }
        else {
            return validTimes.find(reservationTime) != validTimes.end();
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
    return false;
}

bool ReservationDTO::validStatu() const {
    try {
        if (date.empty()) {
            throw std::invalid_argument(DATE_ERROR);
        }
        else {
            return validStatus.find(status) != validStatus.end();
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
    return false;
}

bool ReservationDTO::validCreateTime() const {
    try {
        if (createTime.empty()) {
            throw std::invalid_argument(TIME_ERROR);
        }
        else if (validTime()) {
            return true;
        }
        else {
            throw std::invalid_argument(TIME_CONFLICT);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
    return false;
}
bool ReservationDTO::validUpdateTime() const {
    try {
        if (createTime.empty()) {
            throw std::invalid_argument(TIME_ERROR);
        }
        else if (validTime()) {
            return true;
        }
        else {
            throw std::invalid_argument(UPDATE_TIME_CONFLICT);
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

std::string ReservationDTO::toString() const {
    try {
        if (reservationID.empty() || userID.empty() || computerroomID.empty() || date.empty() || status.empty() || createTime.empty() || updateTime.empty()) {
            throw std::invalid_argument(OPERATE_ABNORMALLY);
        }
        else {
            return std::string("ReservationDTO{reservationID= " + reservationID +
                ", userID=" + userID +
                ", computerroomID=" + computerroomID +
                ", date=" + date +
                ", reservationTime=" + std::to_string(reservationTime) +
                ", status=" + status +
                ", createTime=" + createTime +
                ", updateTime=" + updateTime +
                "}");
        }
    }
    catch (std::invalid_argument& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw e;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
    return std::string(TO_STRING_FALIED);
}