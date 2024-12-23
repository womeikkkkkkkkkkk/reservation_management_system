#pragma once
#include <string>
#include <regex>

class RegexValidator
{
public:
    static bool validateUsername(const std::string& username);//用户名验证  字母、数字和下划线，长度为 4 到 20 个字符
    static bool validatePassward(const std::string& password);//密码验证  至少一个小写字母、一个大写字母、一个数字和一个特殊符号
    static bool validateEmail(const std::string& email);//邮箱验证  邮箱格式规则，支持字母、数字、下划线、点、加号等字符，必须包含 '@' 和 '.'，且 '.' 后至少有两个字母
    static bool validatePhone(const std::string& phone);//手机号验证
};
