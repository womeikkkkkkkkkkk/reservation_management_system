#pragma once
#include "OutputMessages.h"
using namespace std;

//�˵���
void printMainMenu() {
    cout << "======================  ����ԤԼϵͳ  =====================" << endl;
    cout << endl << "�������������" << endl;
    cout << "\t\t -------------------------------\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          1.ѧ������           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          2.��    ʦ           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          3.�� �� Ա           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t|          0.��    ��           |\n";
    cout << "\t\t|                               |\n";
    cout << "\t\t -------------------------------\n";
    cout << "��������ѡ��: ";
}

void printExitMainMenu() {
    cout << "��ӭ��һ��ʹ��!!!" << endl;
}

void printManagerSecondMenu() {
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          1.����˺�            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          2.ɾ���˺�            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          3.�����˺�            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          4.�鿴����            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          5.���ԤԼ            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          6.�޸��û���          |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          7.�޸�����            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t|          0.ע����¼            |\n";
    cout << "\t\t|                                |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "��ѡ�����Ĳ����� " << endl;
}

void printManagerThirst1Menu() {
    cout << "����������˺ŵ�����" << endl;
    cout << "1�����ѧ��" << endl;
    cout << "2�������ʦ" << endl;
}

void printManagerThirst2Menu() {
    cout << "������ɾ���˺ŵ�����" << endl;
    cout << "1�����ѧ��" << endl;
    cout << "2�������ʦ" << endl;
}

void printManagerThirst3Menu() {
    cout << "��ѡ��鿴�˺ŵ����ͣ�" << endl;
    cout << "1���鿴����ѧ��" << endl;
    cout << "2���鿴������ʦ" << endl;
}

void printTeacherSecondMenu() {
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          1.�鿴����ԤԼ          |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          2.���ԤԼ              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          3.�޸��û���            |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          4.�޸�����              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|          0.ע����¼              |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "��ѡ�����Ĳ����� " << endl;
}

void printTeacherThirst1Menu() {
}

void printTeacherThirst2Menu() {
}

void printStudentSecondMenu() {
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          1.����ԤԼ             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          2.�鿴�ҵ�ԤԼ         |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          3.�鿴����ԤԼ         |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          4.ȡ��ԤԼ             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          5.�޸��û���           |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          6.�޸�����             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|          0.ע����¼             |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "��ѡ�����Ĳ����� " << endl;
}

void printStudentThirst1Mneu() {
}

void printStudentThirst2Menu() {
}

//�쳣��
void printInputError() {
    cout << "��������������ѡ��" << endl;
}

void printFileNotFound() {
    cout << "No File" << endl;
}

//��½��
void printInputStudentId() {
    cout << "������ѧ�ţ�" << endl;
}

void printInputTeacherId() {
    cout << "������ְ���ţ�" << endl;
}

void printInputManagerId() {
    cout << "���������Ա�˺ţ�" << endl;
}

void printInputPassword() {
    cout << "���������룺" << endl;
}

void printPasswardError() {
    cout << "�������" << endl;
}

void printIdError() {
    cout << "ID������" << endl;
}

void printLoginStudentSuccess() {
    cout << "ѧ����¼�ɹ�" << endl;
}

void printLoginTeacherSuccess() {
    cout << "��ʦ��¼�ɹ�" << endl;
}

void printLoginManagerSuccess() {
    cout << "����Ա��¼�ɹ�" << endl;
}

void printLoginStudentFailed() {
    cout << "ѧ����¼ʧ��" << endl;
}

void printLoginTeacherFailed() {
    cout << "��ʦ��¼ʧ��" << endl;
}

void printLoginManagerFailed() {
    cout << "����Ա��¼ʧ��" << endl;
}

void printIllegalLogin() {
    cout << "�Ƿ���¼" << endl;
}

//������
void LOG() {
    system("pause");
    system("cls");
}
void TMP() {
    system("pause");
}
void CLEAR() {
    system("cls");
}

//��ʾ��
///����Ա�����˵�����
void printAddAccount() {
    cout << "����˺�" << endl;
}

void printStudentIdDuplicate() {
    cout << "ѧ���ظ�������������" << endl;
}

void printTeacherIdDuplicate() {
    cout << "ְ�����ظ�������������" << endl;
}

void printCurrentStudentNumber(int studentnums) {
    cout << "��ǰѧ������Ϊ��" << studentnums << endl;
}

void printCurrentTeacherNumber(int teachernums) {
    cout << "��ǰ��ʦ����Ϊ��" << teachernums << endl;
}

void printAddSuccess() {
    cout << "��ӳɹ�" << endl;
}

void printRemovePerson() {
    cout << "ɾ���˺�" << endl;
}

void printFindPerson() {
    cout << "�����˺�" << endl;
}

void printViewAccount() {
    cout << "�鿴�˺�" << endl;
}

void printAllTeacherInfo() {
    cout << "������ʦ��Ϣ���£�" << endl;
}

void printAllStudentInfo() {
    cout << "����ѧ����Ϣ���£�" << endl;
}

void printViewComputerRoom() {
    cout << "�鿴����" << endl;
}

void printCurrentComputerNumber(int computernums) {
    cout << "��ǰ��������Ϊ��" << computernums << endl;
}

void printAllComputerInfo() {
    cout << "������Ϣ���£�" << endl;
}

void printClearReservation() {
    cout << "���ԤԼ" << endl;
}

void printAllClearSucces() {
    cout << "��ճɹ���" << endl;
}

void printResetName() {
    cout << "�޸�����" << endl;
}

void printResetPassward() {
    cout << "�޸����룬������ԭ����������룡" << endl;
}
void printResetPasswardSuccess() {
    cout << "�޸�����ɹ���" << endl;
}
void printResetPasswardFalied() {
    cout << "�޸�����ʧ�ܣ�����ԭ�����Ƿ���ȷ��" << endl;
}

void printResetNameSuccess() {
    cout << "�޸��û����ɹ�" << endl;
}

void printResetNameFalied() {
    cout << "�޸��û���ʧ�ܣ����Ժ�����" << endl;
}

//
///��ʦ�����˵�����
void printViewAllOrder() {
    cout << "�鿴����ԤԼ" << endl;
}

void printValidOrder() {
    cout << "���ԤԼ" << endl;
}

void printMemoryOrder1() {
    cout << "����˵�ԤԼ��¼���£�" << endl;
}

void printMemoryOrder2() {
    cout << "��������˵�ԤԼ��¼,0������" << endl;
}

void printMemoryOrder3() {
    cout << "��������˽��" << endl;
    cout << "1��ͨ��" << endl;
    cout << "2����ͨ��" << endl;
}
void printMemoryOrder4() {
    cout << "�����ϣ�" << endl;
}
//
///ѧ�������˵�����
void printApplyOrder1() {
    cout << "��������ʱ��Ϊ��һ�����壡" << endl;
    cout << "����������ԤԼ��ʱ�䣺" << endl;
    cout << "1����һ" << endl;
    cout << "2���ܶ�" << endl;
    cout << "3������" << endl;
    cout << "4������" << endl;
    cout << "5������" << endl;
}

void printApplyOrder2() {
    cout << "����������ԤԼ��ʱ��Σ�" << endl;
    cout << "1������" << endl;
    cout << "2������" << endl;
}

void printApplyOrder3(std::vector<ComputerRoom>& vCom) {
    cout << "��ѡ�������" << endl;
    cout << "1�Ż���������" << vCom[0].GetMax() << endl;
    cout << "2�Ż���������" << vCom[1].GetMax() << endl;
    cout << "3�Ż���������" << vCom[2].GetMax() << endl;
}

void printApplySuccess() {
    cout << "ԤԼ�ɹ��������" << endl;
}

void printMyOrderError() {
    cout << "��ԤԼ��¼" << endl;
}

void printAllOrderError() {
    cout << "��ԤԼ��¼" << endl;
}

void printDeleteOrder1() {
    cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
    cout << "����*****�ɷ���" << endl;
}

void printDeleteOrder2() {
    cout << "������ȡ���ļ�¼,0������" << endl;
}

///���ö����˵�����
void printLogoutSuccess() {
    cout << "ע���ɹ�" << endl;
}

void printInputName() {
    cout << "������������" << endl;
}