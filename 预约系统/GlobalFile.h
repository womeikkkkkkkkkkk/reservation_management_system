#pragma once
#pragma once
#ifndef GLOBALFILE_H
#define GLOBALFILE_H
#include <string>

#define ADMIN_FILE "Admin.txt"//管理员表
#define STUDENT_FILE "Student.txt"//学生表
#define TEACHER_FILE "Teacher.txt"//教师表
#define COMPUTER_FILE "ComputerRoom.txt"//机房表
#define ORDER_FILE "Order.txt"//预约表
#define EXCEPTIONLOG "Exception.log"//日志
#define KEY "Key.txt"//密钥文件

const int  NULLID = -1;//初始化ID
const int NULLCONTAINER = -1;//初始化容量

const std::string LOGIN_INIT_ID = "";
const std::string LOGIN_INIT_NAME = "";
const bool LOGIN_INIT_STATUS = false;

// 0 取消的预约   1 审核中   2 已预约 - 1 预约失败
const std::string CANCELLED_APPOINEDMENT = "0";
const std::string UNDER_REVIEW = "1";
const std::string APPOINTMENT = "2";
const std::string APPOINTMENT_FALIED = "-1";
const std::string MORNING = "上午";
const std::string AFTERNOON = "下午";
const std::string APPOINTMENT_DATE_WEEK = "预约日期： 周";
const std::string TIME_SLOT = "时段：";
const std::string STUDENT_ID = "学号：";
const std::string TEACHER_ID = "职工号：";
const std::string NAME = "姓名：";
const std::string COMPUTER_ROOM = "机房：";
const std::string STATE = "状态：";
const std::string UNDER_VIEW = "审核中";
const std::string APPOINTMENT_SUCCESSFUL = "预约成功";
const std::string REVIEW_DISAPPROVED_APPOINTMENT_FAILED = "审核未通过，预约失败";
const std::string APPOINTMENT_CANCELLED = "预约已取消";
const std::string COMPUTER_ROOM_NUMBER = "机房编号：";
const std::string MAXIMUM_CAPACITY_OF_COMPUTER_ROOM = "机房最大容量：";

const std::string PASSWARD = "密码为：";
const std::string MANAGER_LOGIN_SUCCESS = "管理员的ID正确、密码正确";
const std::string STUDENT_LOGIN_SUCCESS = "学生的ID正确、密码正确";
const std::string TEACHER_LOGIN_SUCCESS = "教师的ID正确、密码正确";
const std::string CREATER_MANAGER_FALIED = "内存分配失败，无法创建管理员对象";
const std::string CREATER_STUDENT_FALIED = "内存分配失败，无法创建学生对象";
const std::string CREATER_TEACHER_FALIED = "内存分配失败，无法创建教师对象";
const std::string CREATER_MANAGER_SUCCESS = "创建管理员成功";
const std::string CREATER_STUDENT_SUCCESS = "创建学生成功";
const std::string CREATER_TEACHER_SUCCESS = "创建教师成功";
const std::string PASSWARD_ERROR = "密码错误";
const std::string ID_NO_EXIST = "Id不存在";
const std::string ILLEGAL_LOGIN = "非法登录";

const std::string OPERATE_ABNORMALLY = "运行异常";
const std::string UNKNOWN_EXCEPTION_OCCURRED = "出现未知异常";
const std::string LOAD_FILE_ERROR = "文件读取出现异常";

const std::string DATA_SIZE_FILL_MARCH_CORRECT = "数据长度符合,填充值合理,填充数据一致";
const std::string DATA_SIZE_ERROR = "数据长度不符合";
const std::string DATA_FILL_ERROR = "填充值不合理";
const std::string DATA_MARCH_ERROR = "填充数据不一致";

const std::string KEY_NO_EXIST = "密钥不存在";

const std::string RESETPASSWARD_SUCCESS = "修改密码成功";
const std::string RESETPASSWARD_FALIED = "修改密码失败";
const std::string RESETNAME_SUCCESS = "修改用户名成功";
const std::string RESETNAME_FALIED = "修改用户名失败";

const std::string ADD_STUDENT_SUCCESS = "学生添加成功";
const std::string ADD_STUDENT_FALIED = "学生添加失败";

const std::string SHOW_ALL_PERSON_SUCCESS = "显示所有信息成功";
const std::string SHOW_ALL_PERSON_FALIED = "显示所有信息失败";

const std::string STUDENT_NO_EXIST = "该学生不存在，请确认后查找";
const std::string STUDENT_EXIST = "查找学生成功";
const std::string TEACHER_NO_EXIST = "该教师不存在，请确认后查找";
const std::string TEACHER_EXIST = "查找教师成功";
const std::string FIND_FALIED = "查找失败";

const std::string CIN_ERROR = "输入错误";
const std::string CIN_SUCCESS = "输入正确";

const std::string TIME_STYLE_ERROR = "日期时间格式错误";
const std::string TIME_STYLE_SUCCESS = "日期时间格式正确";
const std::string TIME_STYLE_CONFLICT = "日期时间格式冲突";

const std::string CREATE_TIME_ERROR = "创建时间错误";
const std::string CREATE_TIME_SUCCESS = "创建时间成功";
const std::string CREATE_TIME_FALIED = "创建时间失败";
const std::string CREATE_TIME_CONFLICT = "创建时间冲突";

const std::string UPDATE_TIME_ERROR = "更新时间错误";
const std::string UPDATE_TIME_SUCCESS = "更新时间成功";
const std::string UPDATE_TIME_FALIED = "更新时间失败";
const std::string UPDATE_TIME_CONFLICT = "更新时间冲突";

const std::string STATUS_ERROR = "状态错误";
const std::string STATUS_SUCCESS = "状态成功";
const std::string STATUS_FALIED = "状态失败";
const std::string STATUS_CONFLICT = "状态冲突";

const std::string TIME_ERROR = "时间错误";
const std::string TIME_SUCCESS = "时间成功";
const std::string TIME_FALIED = "时间失败";
const std::string TIME_CONFLICT = "时间冲突";

const std::string DATE_ERROR = "日期错误";
const std::string DATE_SUCCESS = "日期成功";
const std::string DATE_FALIED = "日期失败";
const std::string DATE_CONFLICT = "日期冲突";

const std::string LOGOUT_ERROR = "退出错误";
const std::string LOGOUT_SUCCESS = "退出成功";
const std::string LOGOUT_FALIED = "退出失败";

const std::string TO_STRING_ERROR = "转换字符串错误";
const std::string TO_STRING_SUCCESS = "转换字符串成功";
const std::string TO_STRING_FALIED = "转换字符串失败";

const std::string POTENTIAL_SQL_INJECTION_DETECTED = "检测到潜在的SQL注入攻击";
const std::string MYSQL_STMT_INIT_FALIED = "初始化MYSQL_STMT失败";
const std::string MYSQL_STMT_PREPARE_FALIED = "准备MYSQL_STMT失败";
const std::string MYSQL_STMT_PARAM_FALIED = "设置MYSQL_STMT参数失败";
const std::string MYSQL_STMT_EXECUTE_FAILED = "执行MYSQL_STMT失败";
const std::string MYSQL_INIT_STATEMENT_FALIED = "初始化MYSQL语句失败";
const std::string MYSQL_PREPARE_STATEMENT_FALIED = "准备语句失败：";
const std::string MYSQL_BIND_PAEAMETERS_BIND_FALIED = "绑定参数失败：";
const std::string MYSQL_EXECUTE_STATEMENT_FALIED = "执行语句失败：";
const std::string MYSQ_GET_RESULT_METADATA_FALIED = "获取结果元数据失败：";
enum {
    // 0学生  1教师  2 管理员
    STUDENTID,
    TEACHERID,
    MANAGERID
};
enum {
    //0有效  1 无效
    VALIDNUMS,
    UNVALIDNUMS
};
#endif 