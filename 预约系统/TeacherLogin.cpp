#pragma once
#include "TeacherLogin.h"
#include "Utils.h"
#include "ExceptionLog.h"

void TeacherLogin(std::string FileName) {
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

        int id;
        std::string passward;
        printInputTeacherId();
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
                    logMsg = Utils::GetCurrentTime(TEACHER_LOGIN_SUCCESS);
                    printLoginTeacherSuccess();
                    exceptionLog.LogException(logMsg);//��֤ͨ����Ϣ

                    person = new Teacher(id, fname, passward);
                    if (person == nullptr) {//�ڴ��Ƿ����ɹ�
                        printLoginTeacherFailed();
                        logMsg = Utils::GetCurrentTime(CREATER_TEACHER_FALIED);
                        exceptionLog.LogException(logMsg);//����ʧ��
                    } 
                    else{
                        logMsg = Utils::GetCurrentTime(CREATER_TEACHER_SUCCESS);
                        exceptionLog.LogException(logMsg);//����ɹ�
                        TeacherSecondMenu(person);//�����ʦ�����˵�
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
            logMsg = Utils::GetCurrentTime(ILLEGAL_LOGIN);
            exceptionLog.LogException(logMsg);
        }
    }
    catch (const std::ios_base::failure& e) {
        std::string logMsg = Utils::GetCurrentTime(LOAD_FILE_ERROR);
        exceptionLog.LogException(logMsg);
        return;
    }
    catch (const std::runtime_error& e) {
        std::string logMsg = Utils::GetCurrentTime(OPERATE_ABNORMALLY);
        exceptionLog.LogException(logMsg);
    }
    catch (...) {
        std::string logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
    }
}