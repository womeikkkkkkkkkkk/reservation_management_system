#pragma once
#include "ManagerSecondMenuIn.h"
#include "Utils.h"
#include "ExceptionLog.h"

void ManagerLogin(std::string FileName)
{
    // ���ݳ�ʼ��
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    try
    {
        std::ifstream ifs;
        ifs.open(FileName, std::ios::in);
        if (!ifs.is_open())
        {
            printFileNotFound();
            ifs.close();
            return;
        }
        // �����˺�����
        Identity* person = nullptr;

        std::string name;
        std::string passward;
        printInputManagerId();
        std::cin >> name;
        printInputPassword();
        std::cin >> passward;
        // ��֤
        std::string fname;
        std::string encryptedFpassward;
        std::string logMsg;

        bool flag = false;
        while (ifs >> fname && ifs >> encryptedFpassward)
        {
            if (name == fname)
            {
                flag = true;
                // ����
                Aes aes;
                std::string key = aes.GetKey(); // ��ȡ��Կ
                // ���ܴ��ļ���ȡ������
                std::string decryptedPassward = Aes::Decrypt(encryptedFpassward, key);
                if (passward == decryptedPassward)
                {
                    // ��֤ͨ��
                    logMsg = Utils::GetCurrentTimes(MANAGER_LOGIN_SUCCESS);
                    printLoginManagerSuccess();
                    exceptionLog.LogException(logMsg); // ��֤ͨ����Ϣ

                    person = new Manager(name, passward);
                    if (person == nullptr)
                    { // �ڴ��Ƿ����ɹ�
                        printLoginManagerFailed();
                        logMsg = Utils::GetCurrentTimes(CREATER_MANAGER_FALIED);
                        exceptionLog.LogException(logMsg); // ����ʧ��
                    }
                    else
                    {
                        logMsg = Utils::GetCurrentTimes(CREATER_MANAGER_SUCCESS);
                        exceptionLog.LogException(logMsg); // ����ɹ�
                        ManagerSecondMenu(person);         // �������Ա�����˵�
                        return;
                    }
                }
                else
                {
                    printPasswardError(); // �������
                    logMsg = Utils::GetCurrentTimes(PASSWARD_ERROR);
                    exceptionLog.LogException(logMsg);
                    return;
                }
            }
        }
        if (flag == false)
        { // ID������
            printIdError();
            logMsg = Utils::GetCurrentTimes(ID_NO_EXIST);
            exceptionLog.LogException(logMsg);
        }
        else
        { // �Ƿ���¼
            printIllegalLogin();
            logMsg = Utils::GetCurrentTimes(ILLEGAL_LOGIN);
            exceptionLog.LogException(logMsg);
        }
    }
    catch (...)
    {
        std::string logMsg = Utils::GetCurrentTimes(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return;
    }
}