#pragma once
#include "Student.h"

Student::Student()
{
    this->id = NULLID;
}

Student::Student(int id, std::string name, std::string passward)
{
    this->id = id;
    this->SetName(name);
    this->SetPasswards(passward);

    std::ifstream ifs;
    ifs.open(COMPUTER_FILE, std::ios::in);

    ComputerRoom c;
    while (ifs >> c)
    {
        vCom.push_back(c);
    }
    ifs.close();
}

void Student::operMenu()
{
    printStudentSecondMenu();
}

std::istream& operator>>(std::istream& is, Student& s)
{
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

void Student::ReSetName(Identity& person, const std::string name)
{
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try
    {
        person.SetName(name);
        printResetNameSuccess();
        logMsg = Utils::GetCurrentTimes(RESETNAME_SUCCESS);
        exceptionLog.LogException(logMsg);
    }
    catch (...)
    {
        logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTimes(RESETNAME_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Student::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward)
{
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try
    {
        std::string fpassward = person.GetPassward();
        Aes aes;
        std::string key = aes.GetKey(); // 获取密钥
        std::string decryptedPassward = Aes::Decrypt(fpassward, key);
        if (decryptedPassward == passward)
        {
            person.SetPasswards(passward);
            printResetPasswardSuccess();
            logMsg = Utils::GetCurrentTimes(RESETPASSWARD_SUCCESS);
            exceptionLog.LogException(logMsg);
        }
        else
        {
            logMsg = Utils::GetCurrentTimes(RESETPASSWARD_FALIED);
            exceptionLog.LogException(logMsg);
            return;
        }
    }
    catch (...)
    {
        logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return;
    }
};

void Student::SetId(const int& id)
{
    this->id = id;
}

void Student::SetName(const std::string& name)
{
    this->Identity::SetName(name);
}

void Student::SetPassward(const std::string& passward)
{
    this->SetPasswards(passward);
}

int Student::GetId() const
{
    return this->id;
}

std::string Student::GetName() const
{
    return this->Identity::GetName();
}

std::string Student::GetPassward() const
{
    Aes aes;
    std::string key = aes.GetKey(); // 获取密钥
    std::string decryptedPassward = Aes::Decrypt(this->Identity::GetPassward(), key);
    return decryptedPassward;
}

void Student::ApplyOrder()
{
    printApplyOrder1();
    int date = 0;
    int interval = 0;
    int room = 0;
    while (true)
    {
        std::cin >> date;
        if (1 <= date && date <= 5)
        {
            break;
        }
        printInputError();
    }
    printApplyOrder2();
    while (true)
    {
        std::cin >> interval;
        if (interval == 1 || interval == 2)
        {
            break;
        }
        printInputError();
    }
    printApplyOrder3(vCom);
    while (true)
    {
        std::cin >> room;
        if (room == 1 || room == 2 || room == 3)
        {
            break;
        }
        printInputError();
    }
    printApplySuccess();

    std::ofstream ofs(ORDER_FILE, std::ios::app);

    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "stuId:" << this->GetId() << " ";
    ofs << "stuName:" << this->GetName() << " ";
    ofs << "roomId:" << room << " ";
    ofs << "status:" << 1 << std::endl;

    ofs.close();
    LOG();
}

void Student::ShowMyOrder()
{
    OrderFile of;

    if (of.GetSize() == 0)
    {
        printMyOrderError();
        LOG();
        return;
    }

    for (int i = 0; i < of.GetSize(); i++)
    {
        if (atoi(of.OrderData[i]["studentid"].c_str()) == this->GetId())
        { // ID匹配，只要自己的记录
            std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
            std::cout << TIME_SLOT << (of.OrderData[i]["interval"] == UNDER_REVIEW ? MORNING : AFTERNOON);
            std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
            std::string status = STATE; // 0 取消的预约   1 审核中   2 已预约 -1 预约失败

            if (of.OrderData[i]["status"] == UNDER_REVIEW)
            {
                status += UNDER_VIEW;
            }
            else if (of.OrderData[i]["status"] == APPOINTMENT)
            {
                status += APPOINTMENT_SUCCESSFUL;
            }
            else if (of.OrderData[i]["status"] == APPOINTMENT_FALIED)
            {
                status += REVIEW_DISAPPROVED_APPOINTMENT_FAILED;
            }
            else if (of.OrderData[i]["status"] == CANCELLED_APPOINEDMENT)
            {
                status += APPOINTMENT_CANCELLED;
            }
            std::cout << status << std::endl;
        }
    }
    LOG();
}

void Student::ShowAllOrder()
{
    OrderFile of;

    if (of.GetSize() == 0)
    {
        printMyOrderError();
        LOG();
        return;
    }

    for (int i = 0; i < of.GetSize(); i++)
    {
        std::cout << i + 1 << "、 ";

        std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
        std::cout << TIME_SLOT << (of.OrderData[i]["interval"] == UNDER_REVIEW ? MORNING : AFTERNOON);
        std::cout << STUDENT_ID << of.OrderData[i]["stuId"];
        std::cout << NAME << of.OrderData[i]["stuName"];
        std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
        std::string status = STATE; // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
        if (of.OrderData[i]["status"] == UNDER_REVIEW)
        {
            status += UNDER_VIEW;
        }
        else if (of.OrderData[i]["status"] == APPOINTMENT)
        {
            status += APPOINTMENT_SUCCESSFUL;
        }
        else if (of.OrderData[i]["status"] == APPOINTMENT_FALIED)
        {
            status += REVIEW_DISAPPROVED_APPOINTMENT_FAILED;
        }
        else if (of.OrderData[i]["status"] == CANCELLED_APPOINEDMENT)
        {
            status += APPOINTMENT_CANCELLED;
        }
        std::cout << status << std::endl;
    }
    LOG();
}

void Student::CancelOrder()
{
    OrderFile of;
    if (of.GetSize() == 0)
    {
        printAllOrderError();
        LOG();
        return;
    }
    printDeleteOrder1();

    std::vector<int> v;
    int index = 1;

    for (int i = 0; i < of.GetSize(); i++)
    {
        if (atoi(of.OrderData[i]["stuId"].c_str()) == this->GetId())
        {
            if (of.OrderData[i]["status"] == UNDER_REVIEW || of.OrderData[i]["status"] == APPOINTMENT)
            {
                v.push_back(i);
                std::cout << index++ << "、 ";
                std::cout << APPOINTMENT_DATE_WEEK << of.OrderData[i]["date"];
                std::cout << TIME_SLOT << (of.OrderData[i]["interval"] == UNDER_REVIEW ? MORNING : AFTERNOON);
                std::cout << COMPUTER_ROOM << of.OrderData[i]["roomId"];
                std::string status = STATE; // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
                if (of.OrderData[i]["status"] == UNDER_REVIEW)
                {
                    status += UNDER_VIEW;
                }
                else if (of.OrderData[i]["status"] == APPOINTMENT)
                {
                    status += APPOINTMENT_SUCCESSFUL;
                }
                std::cout << status << std::endl;
            }
        }
    }

    printDeleteOrder2();
    int select = 0;
    while (true)
    {
        std::cin >> select;
        if (0 <= select && select <= v.size())
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.OrderData[v[select - 1]]["status"] = CANCELLED_APPOINEDMENT;
                of.UpdateOrder();
            }
        }
    }
    LOG();
}