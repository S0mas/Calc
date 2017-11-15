#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>

class Logger
{
public:
    Logger(){}

    void printInfo(const std::string& msg) const        { printLog("INF: " + msg); }
    void printWarning(const std::string& msg) const     { printLog("WRN: " + msg); }
    void printError(const std::string& msg) const       { printLog("ERR: " + msg); }
    void printNormal(const std::string& msg) const      { printLog(msg); }
private:
    void printLog(const std::string& msg) const         { std::cout << msg << std::endl; }
};

#endif // LOGGER_H
