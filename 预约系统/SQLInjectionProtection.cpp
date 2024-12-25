#include "SQLInjectionProtection.h"

bool SQLInjectionProtection::isValidInput(const std::string& input)const {
    return !std::regex_search(input, unsafePatterns);
}

std::string SQLInjectionProtection::sanitizeInput(const std::string& input)const {
    std::string escapedInput = input;
    size_t pos = 0;
    while ((pos == escapedInput.find("'", pos)) != std::string::npos) {
        escapedInput.replace(pos, 1, "''");
        pos += 2;
    }
    return escapedInput;
}