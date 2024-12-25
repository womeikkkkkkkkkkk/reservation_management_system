#pragma once
#ifndef SQLINJECTIONPROTECTION_H
#define SQLINJECTIONPROTECTION_H
#include <string>
#include <regex>
#include <algorithm>
#include <cctype>

class SQLInjectionProtection {
private:
    const std::regex unsafePatterns;//ÕýÔò
public:
    SQLInjectionProtection() : unsafePatterns("('.+--)|(\\b(select|insert|update|delete|drop|union|create|alter|exec|grant|rename|truncate|declare|alter|show|use|;|--|#)\\b)", std::regex::icase) {}
    bool isValidInput(const std::string& input) const;//¼ìÑé×Ö·û´®
    std::string sanitizeInput(const std::string& input) const;
};
#endif