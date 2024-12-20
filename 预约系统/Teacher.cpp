#pragma once
#include "Teacher.h"

Teacher::Teacher() {
    this->id = NULLID;
}

Teacher::Teacher(int id, std::string name, std::string passward) {
    this->id = id;
    this->SetName(name);
    this->SetPasswards(passward);
}

void Teacher::operMenu() {
    printTeacherSecondMenu();
}

void Teacher::ReSetName(Identity& person, const std::string name) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        person.SetName(name);
        printResetNameSuccess();
        logMsg = Utils::GetCurrentTime(RESETNAME_SUCCESS);
        exceptionLog.LogException(logMsg);
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(RESETNAME_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Teacher::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        std::string fpassward = person.GetPassward();
        Aes aes;
        std::string key = aes.GetKey();// 获取密钥
        std::string decryptedPassward = Aes::Decrypt(fpassward, key);
        if (decryptedPassward == passward) {
            printResetPasswardSuccess();
            person.SetPasswards(passward);
            logMsg = Utils::GetCurrentTime(RESETPASSWARD_SUCCESS);
            exceptionLog.LogException(logMsg);
        }
        else {
            printResetPasswardFalied();
            logMsg = Utils::GetCurrentTime(RESETPASSWARD_FALIED);
            exceptionLog.LogException(logMsg);
            return;
        }
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(RESETPASSWARD_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

std::istream& operator>>(std::istream& is, Teacher& s) {
    int id;
    std::string name;
    std::string passward;
    is >> id;
    is >> name;
    is >> passward;
    s.SetId(id);
    s.SetName(name);
    s.SetPassward(passward);
    return is;
}

void Teacher::SetId(const int& id) {
    this->id = id;
}

void Teacher::SetName(const std::string& name) {
    this->Identity::SetName(name);
}

void Teacher::SetPassward(const std::string& passward) {
    this->Identity::SetPasswards(passward);
}

int Teacher::GetId()const {
    return this->id;
}

std::string Teacher::GetName()const {
    return this->Identity::GetName();
}

std::string Teacher::GetPassward()const {
    Aes aes;
    std::string key = aes.GetKey();// 获取密钥
    std::string decryptedPassward = Aes::Decrypt(this->Identity::GetPassward(), key);
    return decryptedPassward;
}

void Teacher::ShowAllOrder() {
    OrderFile of;

    if (of.GetSize() == 0) {
        printMyOrderError();
        LOG();
        return;
    }

    for (int i = 0; i < of.GetSize(); i++) {
        std::cout << i + 1 << "、 ";

        std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
        std::cout << TIME_SLOT << (of.OrderData[i]["interval"] == UNDER_REVIEW ? MORNING : AFTERNOON);
        std::cout << STUDENT_ID << of.OrderData[i]["stuId"];
        std::cout << NAME << of.OrderData[i]["stuName"];
        std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
        std::string status = STATE;  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
        if (of.OrderData[i]["status"] == UNDER_REVIEW) {
            status += UNDER_VIEW;
        }
        else if (of.OrderData[i]["status"] == APPOINTMENT) {
            status += APPOINTMENT_SUCCESSFUL;
        }
        else if (of.OrderData[i]["status"] == APPOINTMENT_FALIED) {
            status += REVIEW_DISAPPROVED_APPOINTMENT_FAILED;
        }
        else if (of.OrderData[i]["status"] == CANCELLED_APPOINEDMENT) {
            status += APPOINTMENT_CANCELLED;
        }
        std::cout << status << std::endl;
    }
    LOG();
}

void Teacher::ValidOrder() {
    OrderFile of;

    if (of.GetSize() == 0) {
        printMyOrderError();
        LOG();
        return;
    }
    std::vector<int> v;
    int index = 0;
    for (int i = 0; i < of.GetSize(); i++) {
        if (of.OrderData[i]["status"] == UNDER_REVIEW) {
            v.push_back(i);
            std::cout << ++index << "、 ";

            std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
            std::cout << TIME_SLOT << (of.OrderData[i]["interval"] == UNDER_REVIEW ? MORNING : AFTERNOON);
            std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
            std::string status = STATE;  // 0取消的预约   1 审核中   2 已预约  -1 预约失败
            if (of.OrderData[i]["status"] == UNDER_REVIEW)
            {
                status += UNDER_VIEW;
            }
            std::cout << status << std::endl;
        }
    }
    printMemoryOrder2();
    int select = 0;
    int ret = 0;
    while (true) {
        std::cin >> select;
        if (0 <= select && select <= v.size()) {
            if (select == 0) {
                break;
            }
            else {
                printMemoryOrder3();
                std::cin >> ret;
                if (ret == 1) {
                    of.OrderData[v[select - 1]]["status"] = APPOINTMENT;
                }
                else {
                    of.OrderData[v[select - 1]]["status"] = APPOINTMENT_FALIED;
                }
                of.UpdateOrder();
                printMemoryOrder4();
                break;
            }
        }
        printInputError();
    }
    LOG();
}