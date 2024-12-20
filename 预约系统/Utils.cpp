#include "Utils.h"

std::string Utils::GetCurrentTime() {
    std::time_t CurrentTime = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&CurrentTime));
    return std::string(buffer);
}

std::string Utils::GetCurrentTime(std::string s) {
    std::time_t CurrentTime = std::time(nullptr);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&CurrentTime));
    return "[" + std::string(buffer) + "]" + s;
}