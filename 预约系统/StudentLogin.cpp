#pragma once
#include "StudentLogin.h"
#include "ExceptionLog.h"
#include "Utils.h"

void StudentLogin(std::string FileName) {
    //���ݳ�ʼ��
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    try {
        std::ifstream ifs;
        ifs.open(FileName, std::ios::in);
        if (!ifs.is_open()) {
            printFileNotFound();
            ifs.close();
            return;
        }
        //�����˺�����
        Identity* person = nullptr;

        int id = 0;
        std::string passward;
        printInputStudentId();
        std::cin >> id;
        printInputPassword();
        std::cin >> passward;
        //��֤
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
                if (passward == encryptedFpassward) {//��֤ͨ��
                    logMsg = Utils::GetCurrentTime(STUDENT_LOGIN_SUCCESS);
                    printLoginStudentSuccess();
                    exceptionLog.LogException(logMsg);//��֤ͨ����Ϣ

                    person = new Student(id, fname, passward);
                    if (person == nullptr) {//�ڴ��Ƿ����ɹ�
                        printLoginStudentFailed();
                        logMsg = Utils::GetCurrentTime(CREATER_STUDENT_FALIED);
                        exceptionLog.LogException(logMsg);//����ʧ��
                    }
                    else {
                        logMsg = Utils::GetCurrentTime(CREATER_STUDENT_SUCCESS);
                        exceptionLog.LogException(logMsg);//����ɹ�
                        StudentMenu(person);//����ѧ�������˵�
                        return;
                    }
                }
                else {
                    printPasswardError();//�������
                    logMsg = Utils::GetCurrentTime(PASSWARD_ERROR);
                    exceptionLog.LogException(logMsg);
                    return;
                }
            }
        }
        if (flag == false) {//ID������
            printIdError();
            logMsg = Utils::GetCurrentTime(ID_NO_EXIST);
            exceptionLog.LogException(logMsg);
        }
        else {//�Ƿ���¼
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