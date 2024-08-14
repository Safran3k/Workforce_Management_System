#include <stdlib.h>
#include <regex>
#include <stdexcept>

namespace inputCheck
{
    bool isInt(std::string str)
    {
        std::regex numberRegex("^[0-9]+$");
        return std::regex_match(str, numberRegex);
    }

    std::invalid_argument ex("Non-numeric argument");

    int stoi(std::string s)
    {
        int retval = 0;
        if(isInt(s))
        {
            retval = atoi(s.c_str());
        }
        else
        {
            throw ex;
        }

        return retval;
    }
}

