#pragma once
#include "StudentLogin.h"
#include "ExceptionLog.h"
#include "Utils.h"

void StudentLogin(std::string FileName) {
    //数据初始化
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    try {
        std::ifstream ifs;
        ifs.open(FileName, std::ios::in);
        if (!ifs.is_open()) {
            printFileNotFound();
            ifs.close();
            return;
        }
        //输入账号密码
        Identity* person = nullptr;

        int id = 0;
        std::string passward;
        printInputStudentId();
        std::cin >> id;
        printInputPassword();
        std::cin >> passward;
        //验证
        int fid;
        std::string fname;
        std::string encryptedFpassward;
        std::string logMsg;

        bool flag = false;
        while (ifs >> fid && ifs >> fname && ifs >> encryptedFpassward) {
            if (id == fid) {
                flag = true;
                Aes aes;
                std::string key = aes.GetKey();
                std::string decryptedPassward = Aes::Decrypt(encryptedFpassward, key);
                if (passward == encryptedFpassward) {//验证通过
                    logMsg = Utils::GetCurrentTime(STUDENT_LOGIN_SUCCESS);
                    printLoginStudentSuccess();
                    exceptionLog.LogException(logMsg);//验证通过信息

                    person = new Student(id, fname, passward);
                    if (person == nullptr) {//内存是否分配成功
                        printLoginStudentFailed();
                        logMsg = Utils::GetCurrentTime(CREATER_STUDENT_FALIED);
                        exceptionLog.LogException(logMsg);//分配失败
                    }
                    else {
                        logMsg = Utils::GetCurrentTime(CREATER_STUDENT_SUCCESS);
                        exceptionLog.LogException(logMsg);//分配成功
                        StudentMenu(person);//进入学生二级菜单
                        return;
                    }
                }
                else {
                    printPasswardError();//密码错误
                    logMsg = Utils::GetCurrentTime(PASSWARD_ERROR);
                    exceptionLog.LogException(logMsg);
                    return;
                }
            }
        }
        if (flag == false) {//ID不存在
            printIdError();
            logMsg = Utils::GetCurrentTime(ID_NO_EXIST);
            exceptionLog.LogException(logMsg);
        }
        else {//非法登录
            printIllegalLogin();
            return;
        }
    }
    catch (const std::ios_base::failure& e) {
        std::string logMsg = Utils::GetCurrentTime(LOAD_FILE_ERROR);
        exceptionLog.LogException(logMsg);
        return;
    }
    catch (...) {
        std::string logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return;
    }
}