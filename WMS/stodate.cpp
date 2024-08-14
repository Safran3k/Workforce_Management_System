#include "stodate.hpp"
#include <regex>
#include <stdexcept>

namespace dateCheck {
    bool isValidDate(const std::string& date) {
        std::regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
        return std::regex_match(date, datePattern);
    }

    std::invalid_argument invalidDateEx("Invalid date format. Please use YYYY-MM-DD format.");

    std::string stodate(const std::string& date) {
        if (isValidDate(date)) {
            return date;
        } else {
            throw invalidDateEx;
        }
    }
}

