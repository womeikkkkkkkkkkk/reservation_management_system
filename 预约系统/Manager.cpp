#pragma once
#include "Manager.h"

std::istream& operator>>(std::istream& is, Manager& s) {
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

bool Manager::TextIdCmp(int fid, std::string text) {
    std::string ftext = std::to_string(fid);
    size_t len_valid_id = ftext.size();
    for (int i = 0; i < text.size(); i++) {
        if (ftext[i] != text[i] || len_valid_id != text.size()) {
            return false;
        }
    }
    return true;
}

Manager::Manager() {
    this->id = NULLID;
}

Manager::Manager(std::string name, std::string passward)
{
    this->SetName(name);
    this->SetPasswards(passward);
    ///容器初始化
    this->InitVector();
    ///获取机房信息
    std::ifstream ifs;
    ifs.open(COMPUTER_FILE, std::ios::in);
    ComputerRoom c;
    while (ifs >> c) {
        vCom.push_back(c);
    }
    printCurrentComputerNumber((int)vCom.size());
    ifs.close();
}

void Manager::operMenu()
{
    printManagerSecondMenu();
}

void Manager::ReSetName(Identity& person, const std::string name) {
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
        printResetNameFalied();
        logMsg += Utils::GetCurrentTime(RESETNAME_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::ReSetPasswards(Identity& person, const std::string passward, const std::string oldpassward) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        if (person.GetPassward() == oldpassward) {
            person.SetPasswards(passward);
            printResetPasswardSuccess();
            logMsg = Utils::GetCurrentTime(RESETPASSWARD_SUCCESS);
            exceptionLog.LogException(logMsg);
        }
        else {
            printResetPasswardFalied();
            logMsg = Utils::GetCurrentTime(RESETPASSWARD_FALIED);
            exceptionLog.LogException(logMsg);
        }
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::SetId(const int& id) {
    this->id = id;
}

void Manager::SetName(const std::string& name) {
    this->Identity::SetName(name);
}

void Manager::SetPassward(const std::string& passward) {
    this->Identity::SetPasswards(passward);
}

int Manager::GetId() const {
    return this->id;
}

std::string Manager::GetName()const {
    return this->Identity::GetName();
}

std::string Manager::GetPassward()const {
    return this->Identity::GetPassward();
}

void Manager::InitVector() {
    //容器初始化
    vStu = std::vector<Student>();
    vTea = std::vector<Teacher>();
    vCom = std::vector<ComputerRoom>();
    //读取初始化
    std::ifstream ifs;
    ifs.open(STUDENT_FILE, std::ios::in);
    if (!ifs.is_open()) {
        printFileNotFound();
        return;
    }
    vStu.clear();
    vTea.clear();
    //读取学生信息
    Student s;
    while (ifs >> s) {
        vStu.push_back(s);
    }
    printCurrentStudentNumber((int)vStu.size());
    ifs.close();
    //读取教师信息
    ifs.open(TEACHER_FILE, std::ios::in);
    Teacher t;
    while (ifs >> t) {
        vTea.push_back(t);
    }
    printCurrentTeacherNumber((int)vTea.size());
    ifs.close();
}

bool Manager::CheckRepeat(const int id, const int type) {
    if (type == STUDENTID) {
        for (std::vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++) {
            if (id == it->GetId()) {
                return true;
            }
        }
    }
    else if (type == TEACHERID) {
        for (std::vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++) {
            if (id == it->GetId()) {
                return true;
            }
        }
    }
    return false;
}

void Manager::AddPerson()
{
    InitVector();
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        printManagerThirst1Menu();
        std::string FileName;
        int flag = -1;
        std::ofstream ofs;
        int select = 0;
        ///判断添加用户类型
        while (true) {
            std::cin >> select;
            if (select == 1) {
                FileName = STUDENT_FILE;
                flag = STUDENTID;
                break;
            }
            else if (select == 2) {
                FileName = TEACHER_FILE;
                flag = TEACHERID;
                break;
            }
            else {
                printInputError();
                continue;
            }
        }
        ///添加用户
        ofs.open(FileName, std::ios::out | std::ios::app);
        int id;
        std::string name;
        std::string passward;

        flag == STUDENTID ? printInputStudentId() : printInputTeacherId();
        while (true) {
            std::cin >> id;
            bool isValid = this->CheckRepeat(id, flag);
            if (isValid) {
                flag == STUDENTID ? printStudentIdDuplicate() : printTeacherIdDuplicate();
            }
            else {
                break;
            }
        }
        printInputName();
        std::cin >> name;
        printInputPassword();
        std::cin >> passward;
        //加密
        Aes aes;
        std::string key = aes.GetKey();
        std::string encryptedPassward = Aes::Encrypt(passward, key);
        ofs << id << " " << name << " " << encryptedPassward << " " << std::endl;
        printAddSuccess();
        logMsg = Utils::GetCurrentTime(ADD_STUDENT_SUCCESS);
        exceptionLog.LogException(logMsg);
        LOG();
        ofs.close();
        this->InitVector();
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(ADD_STUDENT_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::RemovePerson() {
    InitVector();
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        printManagerThirst2Menu();
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(FIND_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::FindPerson(const std::string& text) {
    InitVector();
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        int select = 0;
        while (1) {
            printManagerThirst3Menu();
            std::cin >> select;
            if (select == 1) {
                for (auto i = vStu.begin(); i < vStu.end(); i++) {
                    if ((*i).GetName() == text || TextIdCmp((*i).GetId(), text)) {
                        logMsg = Utils::GetCurrentTime(STUDENT_EXIST);
                        exceptionLog.LogException(logMsg);
                        std::cout << STUDENT_ID << (*i).GetId() << NAME << (*i).GetName() << PASSWARD << (*i).GetPassward() << std::endl;
                        return;
                    }
                }
            }
            else if (select == 2) {
                for (auto i = vTea.begin(); i < vTea.end(); i++) {
                    if ((*i).GetName() == text || TextIdCmp((*i).GetId(), text)) {
                        logMsg = Utils::GetCurrentTime(TEACHER_EXIST);
                        exceptionLog.LogException(logMsg);
                        std::cout << TEACHER_ID << (*i).GetId() << NAME << (*i).GetName() << PASSWARD << (*i).GetPassward() << std::endl;
                        return;
                    }
                }
            }
            else {
                printInputError();
                logMsg = Utils::GetCurrentTime(CIN_ERROR);
                exceptionLog.LogException(logMsg);
            }
        }
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(FIND_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::ShowPerson()
{
    InitVector();
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        int select = 0;
        while (1) {
            printManagerThirst3Menu();
            std::cin >> select;
            if (select == 1) {
                printAllStudentInfo();
                for (auto i = vStu.begin(); i < vStu.end(); i++) {
                    std::cout << STUDENT_ID << (*i).GetId() << NAME << (*i).GetName() << PASSWARD << (*i).GetPassward() << std::endl;
                }
                break;
            }
            else if (select == 2) {
                printAllTeacherInfo();
                for (auto i = vTea.begin(); i < vTea.end(); i++) {
                    std::cout << TEACHER_ID << (*i).GetId() << NAME << (*i).GetName() << PASSWARD << (*i).GetPassward() << std::endl;
                }
                break;
            }
            else {
                printInputError();
                continue;
            }
            LOG();
        }
        LOG();
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(SHOW_ALL_PERSON_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::ShowComputer()
{
    InitVector();
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        printAllComputerInfo();
        for (auto i = vCom.begin(); i < vCom.end(); i++) {
            std::cout << COMPUTER_ROOM_NUMBER << (*i).GetId() << MAXIMUM_CAPACITY_OF_COMPUTER_ROOM << (*i).GetMax() << std::endl;
        }
        LOG();
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(SHOW_ALL_PERSON_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}

void Manager::CleanFile()
{
    InitVector();
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        std::ofstream ofs(ORDER_FILE, std::ios::trunc);
        ofs.close();
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime(SHOW_ALL_PERSON_FALIED);
        exceptionLog.LogException(logMsg);
        return;
    }
}