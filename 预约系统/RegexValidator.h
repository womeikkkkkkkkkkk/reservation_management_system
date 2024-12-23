#pragma once
#include <string>
#include <regex>

class RegexValidator
{
public:
    static bool validateUsername(const std::string& username);//�û�����֤  ��ĸ�����ֺ��»��ߣ�����Ϊ 4 �� 20 ���ַ�
    static bool validatePassward(const std::string& password);//������֤  ����һ��Сд��ĸ��һ����д��ĸ��һ�����ֺ�һ���������
    static bool validateEmail(const std::string& email);//������֤  �����ʽ����֧����ĸ�����֡��»��ߡ��㡢�Ӻŵ��ַ���������� '@' �� '.'���� '.' ��������������ĸ
    static bool validatePhone(const std::string& phone);//�ֻ�����֤
};
