#include "RegexValidator.h"

bool RegexValidator::validateUsername(const std::string& username) {
    std::regex usernameRegex("^[a-zA-Z0-9_]{4,20}$");
    return std::regex_match(username, usernameRegex);
}

bool RegexValidator::validatePassward(const std::string& passward) {
    std::regex passwardRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,20}$");
    return std::regex_match(passward, passwardRegex);
}

bool RegexValidator::validateEmail(const std::string& email) {
    std::regex emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, emailRegex);
}

bool RegexValidator::validatePhone(const std::string& phone) {
    std::regex phoneRegex("^1(3[0-9]|4[5-9]|5[0-3]|5[5-9]|6[0-5]|7[0-8]|8[0-9]|9[1-9])\d{8}$");
    return std::regex_match(phone, phoneRegex);
}