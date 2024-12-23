#pragma once
#include <iostream>
#include <string>

//���ֲ�
#include "LoginManager.h"         // ��¼������
#include "ManagerMenu.h"          // ����Ա�˵�
#include "StudentMenu.h"          // ѧ���˵�
#include "TeacherMenu.h"          // ��ʦ�˵�
#include "MessageManager.h"       // ��Ϣ������
#include "VerificationCodeManager.h" // ��֤�������

//ҵ���߼���
#include "Identity.h"             // �û�����ࣨѧ������ʦ������Ա��
#include "ReservationManager.h"   // ԤԼ������
#include "ComputerRoomManager.h"          // ����������

//���ݲ�
#include "DatabaseManager.h"      // ���ݿ������
#include "StudentDAO.h"           // ѧ�����ݷ��ʶ���
#include "TeacherDAO.h"           // ��ʦ���ݷ��ʶ���
#include "ManagerDAO.h"           // ����Ա���ݷ��ʶ���

//��������
#include "Log.h"                  // ��־����
#include "TimeUtils.h"            // ʱ�乤��
#include "CaptchaUtils.h"         // ��֤�빤����
#include "EncryptionUtils.h"      // ���ܹ�����
using namespace std;

int main()
{
    while (1) {
        int select;
        std::cin >> select;
        if (!isLoggedIn) {
            std::cout << "��¼ʧ��!" << std::endl;
            return 0;
        }

        if (loginManager.getUserRole() == "admin") {
            ManagerMenu managerMenu;
            managerMenu.showMenu();
        }
        else if (loginManager.getUserRole() == "student") {
            StudentMenu studentMenu;
            studentMenu.showMenu();
        }
        else if (loginManager.getUserRole() == "teacher") {
            TeacherMenu teacherMenu;
            teacherMenu.showMenu();
        }
    }
    return 0;
}