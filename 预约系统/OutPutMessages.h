#pragma once
#include <iostream>
#include <vector>
#include "ComputerRoom.h"

//�˵���
///һ���˵���ʾ
void printMainMenu();
void printExitMainMenu();
///����Ա�˵���ʾ
void printManagerSecondMenu();
void printManagerThirst1Menu();
void printManagerThirst2Menu();
///��ʦ�˵���ʾ
void printTeacherSecondMenu();
void printTeacherThirst1Menu();
void printTeacherThirst2Menu();
///ѧ���˵���ʾ
void printStudentSecondMenu();
void printStudentThirst1Mneu();
void printStudentThirst2Menu();

//�쳣��
void printInputError();
void printFileNotFound();

//��¼��
void printInputStudentId();
void printInputTeacherId();
void printInputManagerId();
void printInputPassword();
void printPasswardError();
void printIdError();
void printLoginStudentSuccess();
void printLoginTeacherSuccess();
void printLoginManagerSuccess();
void printLoginStudentFailed();
void printLoginTeacherFailed();
void printLoginManagerFailed();
void printIllegalLogin();

//������
void LOG();
void TMP();
void CLEAR();

//��ʾ��
///�����˵�����
///����Ա�����˵�����

void printAddAccount();
void printStudentIdDuplicate();
void printTeacherIdDuplicate();
void printAddSuccess();
void printInputName();
void printViewAccount();
void printAllTeacherInfo();
void printAllStudentInfo();
void printCurrentStudentNumber(int studentnums);
void printCurrentTeacherNumber(int teachernums);

void printViewComputerRoom();
void printAllComputerInfo();
void printCurrentComputerNumber(int computernums);

void printClearReservation();
void printAllClearSucces();
void printResetName();
void printResetPassward();
void printResetPasswardSuccess();
void printResetPasswardFalied();
void printResetNameSuccess();
void printResetNameFalied();
///��ʦ�����˵�����
void printViewAllOrder();

void printValidOrder();
void printMemoryOrder1();
void printMemoryOrder2();
void printMemoryOrder3();
void printMemoryOrder4();

///ѧ�������˵�����
void printApplyOrder1();
void printApplyOrder2();
void printApplyOrder3(std::vector<ComputerRoom>& vCom);
void printApplySuccess();

void printMyOrderError();

void printAllOrderError();

void printDeleteOrder1();
void printDeleteOrder2();
//������
void printLogoutSuccess();
