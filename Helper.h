#ifndef HELPER_H
#define HELPER_H
#include <cctype>
#include <string>
#include <functional>
#include <cmath>

class Helper
{
public:
    Helper();

    static inline bool isKnownOperator(const std::string& str)
    {
       return str == "+" || str == "-" || str == "*" || str == "/";
    }

    static inline bool constainsOnlyNumbers(const std::string& str)
    {
        for(const char& sign : str)
        {
            if(!isdigit(sign))
                return false;
        }

       return true;
    }

    static inline bool constainsOnlyLettersOrNumbers(const std::string& str)
    {
        for(const char& sign : str)
        {
            if(!isdigit(sign) && !isalpha(sign))
                return false;
        }

       return true;
    }

    static inline std::function<double(double)> getFunction1Arg(const std::string& str)
    {
        if(str == "sin")
            return sin;
        else
            return cos;
    }

    static inline std::function<double(double, double)> getFunction2Arg(const std::string& str)
    {
        if(str == "+")
            return std::plus<double>();
        else if(str == "-")
            return std::minus<double>();
        else if(str == "/")
            return std::divides<double>();
        else
            return std::multiplies<double>();
    }
};

#endif // HELPER_H
