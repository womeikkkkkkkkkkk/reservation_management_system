#pragma once
#pragma once
#include <string>

#define ADMIN_FILE "Admin.txt"//����Ա��
#define STUDENT_FILE "Student.txt"//ѧ����
#define TEACHER_FILE "Teacher.txt"//��ʦ��
#define COMPUTER_FILE "ComputerRoom.txt"//������
#define ORDER_FILE "Order.txt"//ԤԼ��
#define EXCEPTIONLOG "Exception.log"//��־
#define KEY "Key.txt"//��Կ�ļ�

const int  NULLID = -1;//��ʼ��ID
const int NULLCONTAINER = -1;//��ʼ������

const std::string LOGIN_INIT_ID = "";
const std::string LOGIN_INIT_NAME = "";
const bool LOGIN_INIT_STATUS = false;

// 0 ȡ����ԤԼ   1 �����   2 ��ԤԼ - 1 ԤԼʧ��
const std::string CANCELLED_APPOINEDMENT = "0";
const std::string UNDER_REVIEW = "1";
const std::string APPOINTMENT = "2";
const std::string APPOINTMENT_FALIED = "-1";
const std::string MORNING = "����";
const std::string AFTERNOON = "����";
const std::string APPOINTMENT_DATE_WEEK = "ԤԼ���ڣ� ��";
const std::string TIME_SLOT = "ʱ�Σ�";
const std::string STUDENT_ID = "ѧ�ţ�";
const std::string TEACHER_ID = "ְ���ţ�";
const std::string NAME = "������";
const std::string COMPUTER_ROOM = "������";
const std::string STATE = "״̬��";
const std::string UNDER_VIEW = "�����";
const std::string APPOINTMENT_SUCCESSFUL = "ԤԼ�ɹ�";
const std::string REVIEW_DISAPPROVED_APPOINTMENT_FAILED = "���δͨ����ԤԼʧ��";
const std::string APPOINTMENT_CANCELLED = "ԤԼ��ȡ��";
const std::string COMPUTER_ROOM_NUMBER = "������ţ�";
const std::string MAXIMUM_CAPACITY_OF_COMPUTER_ROOM = "�������������";

const std::string PASSWARD = "����Ϊ��";
const std::string MANAGER_LOGIN_SUCCESS = "����Ա��ID��ȷ��������ȷ";
const std::string STUDENT_LOGIN_SUCCESS = "ѧ����ID��ȷ��������ȷ";
const std::string TEACHER_LOGIN_SUCCESS = "��ʦ��ID��ȷ��������ȷ";
const std::string CREATER_MANAGER_FALIED = "�ڴ����ʧ�ܣ��޷���������Ա����";
const std::string CREATER_STUDENT_FALIED = "�ڴ����ʧ�ܣ��޷�����ѧ������";
const std::string CREATER_TEACHER_FALIED = "�ڴ����ʧ�ܣ��޷�������ʦ����";
const std::string CREATER_MANAGER_SUCCESS = "��������Ա�ɹ�";
const std::string CREATER_STUDENT_SUCCESS = "����ѧ���ɹ�";
const std::string CREATER_TEACHER_SUCCESS = "������ʦ�ɹ�";
const std::string PASSWARD_ERROR = "�������";
const std::string ID_NO_EXIST = "Id������";
const std::string ILLEGAL_LOGIN = "�Ƿ���¼";

const std::string OPERATE_ABNORMALLY = "�����쳣";
const std::string UNKNOWN_EXCEPTION_OCCURRED = "����δ֪�쳣";
const std::string LOAD_FILE_ERROR = "�ļ���ȡ�����쳣";

const std::string DATA_SIZE_FILL_MARCH_CORRECT = "���ݳ��ȷ���,���ֵ����,�������һ��";
const std::string DATA_SIZE_ERROR = "���ݳ��Ȳ�����";
const std::string DATA_FILL_ERROR = "���ֵ������";
const std::string DATA_MARCH_ERROR = "������ݲ�һ��";

const std::string KEY_NO_EXIST = "��Կ������";

const std::string RESETPASSWARD_SUCCESS = "�޸�����ɹ�";
const std::string RESETPASSWARD_FALIED = "�޸�����ʧ��";
const std::string RESETNAME_SUCCESS = "�޸��û����ɹ�";
const std::string RESETNAME_FALIED = "�޸��û���ʧ��";

const std::string ADD_STUDENT_SUCCESS = "ѧ����ӳɹ�";
const std::string ADD_STUDENT_FALIED = "ѧ�����ʧ��";

const std::string SHOW_ALL_PERSON_SUCCESS = "��ʾ������Ϣ�ɹ�";
const std::string SHOW_ALL_PERSON_FALIED = "��ʾ������Ϣʧ��";

const std::string STUDENT_NO_EXIST = "��ѧ�������ڣ���ȷ�Ϻ����";
const std::string STUDENT_EXIST = "����ѧ���ɹ�";
const std::string TEACHER_NO_EXIST = "�ý�ʦ�����ڣ���ȷ�Ϻ����";
const std::string TEACHER_EXIST = "���ҽ�ʦ�ɹ�";
const std::string FIND_FALIED = "����ʧ��";

const std::string CIN_ERROR = "�������";
const std::string TIME_STYLE_ERROR = "����ʱ���ʽ����";
enum {
    // 0ѧ��  1��ʦ  2 ����Ա
    STUDENTID,
    TEACHERID,
    MANAGERID
};
enum {
    //0��Ч  1 ��Ч
    VALIDNUMS,
    UNVALIDNUMS
};
