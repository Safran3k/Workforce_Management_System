#include "stod.hpp"
#include <regex>
#include <stdexcept>
#include <string>

namespace inputCheck {
    bool isDouble(const std::string& str) {
        std::regex doubleRegex("^[-+]?[0-9]*\\.?[0-9]+$");
        return std::regex_match(str, doubleRegex);
    }

    std::invalid_argument exDouble("Non-numeric argument for double.");

    double stod(const std::string& s) {
        if (isDouble(s)) {
            return std::stod(s);
        } else {
            throw exDouble;
        }
    }
}

