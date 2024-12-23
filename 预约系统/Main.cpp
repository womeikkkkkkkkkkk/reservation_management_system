#pragma once
#include <iostream>
#include <string>

//表现层
#include "LoginManager.h"         // 登录管理器
#include "ManagerMenu.h"          // 管理员菜单
#include "StudentMenu.h"          // 学生菜单
#include "TeacherMenu.h"          // 教师菜单
#include "MessageManager.h"       // 消息管理器
#include "VerificationCodeManager.h" // 验证码管理器

//业务逻辑层
#include "Identity.h"             // 用户身份类（学生、教师、管理员）
#include "ReservationManager.h"   // 预约管理器
#include "ComputerRoomManager.h"          // 机房管理器

//数据层
#include "DatabaseManager.h"      // 数据库管理器
#include "StudentDAO.h"           // 学生数据访问对象
#include "TeacherDAO.h"           // 教师数据访问对象
#include "ManagerDAO.h"           // 管理员数据访问对象

//公共工具
#include "Log.h"                  // 日志工具
#include "TimeUtils.h"            // 时间工具
#include "CaptchaUtils.h"         // 验证码工具类
#include "EncryptionUtils.h"      // 加密工具类
using namespace std;

int main()
{
    while (1) {
        int select;
        std::cin >> select;
        if (!isLoggedIn) {
            std::cout << "登录失败!" << std::endl;
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