#ifndef IEXPRESSIONTREE_H
#define IEXPRESSIONTREE_H
#include <string>
#include <vector>
#include <iostream>
#include "ExpressionTree.h"
#include <sstream>
#include <istream>
#include <iterator>

class IExpressionTree
{
public:
    IExpressionTree();
    [[ noreturn ]] void run()
    {
        while(true)
        {
            std::vector<std::string> command(splitString(getCommand()));
            if(validateCommand(command))
                processCommand(command);
        }
    }

private:
    std::string getCommand()
    {
        std::string str;

        std::getline(std::cin, str);
        return str;
    }

    std::vector<std::string> splitString(const std::string& str)
    {
        std::stringstream ss(str);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> strVec(begin, end);
        std::copy(strVec.begin(), strVec.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        return strVec;
    }

    bool validateCommand(const std::vector<std::string>& strVec)
    {
        const std::string& command = strVec.front();
        bool result = false;

        if(command == "enter" || command == "join")
            result = validateComandEnterOrJoin(strVec);
        else if(command == "vars" || command == "print")
            result =  validateComandVarsOrPrint(strVec);
        else if(command == "comp")
            result =  validateComandComp(strVec);
        else
            std::cout << "Invalid command!\n" ;

        return result;
    }

    bool validateComandEnterOrJoin(const std::vector<std::string>& strVec)
    {
        for(auto& str : strVec)
        {
            if(!Helper::isKnownOperator(str) && !Helper::constainsOnlyLettersOrNumbers(str))
                return false;
        }
        return true;
    }

    bool validateComandVarsOrPrint(const std::vector<std::string>& strVec)
    {
        return strVec.size() == 1;
    }

    bool validateComandComp(const std::vector<std::string>& strVec)
    {
        for(auto& str : strVec)
        {
            if(!Helper::constainsOnlyNumbers(str) && str != strVec.front())
                return false;
        }

        return strVec.size() - 1 == expTree.getNumberOfVariables();
    }

    void processCommand(std::vector<std::string>& strVec)
    {
        const std::string command = strVec.front();
        strVec.erase(strVec.begin());

        if(command == "enter")
            expTree.createExpTree(strVec);
        else if(command == "join")
        {
            ExpressionTree tempTree;
            tempTree.createExpTree(strVec);
            expTree = expTree + tempTree;
        }
        else if(command == "print")
        {
            for(auto& str : expTree.toStringVec())
                std::cout << str << " ";
            std::cout << std::endl;
        }
        else if(command == "vars")
        {
            expTree.showVariables();
        }
        else if(command == "comp")
        {
            std::vector<double> valuesVec;
            std::transform(strVec.begin(), strVec.end(), std::back_inserter(valuesVec),
                           [](const std::string& str) { return std::stod(str); });
            expTree.setVariablesValues(valuesVec);
        }
        else
            std::cout << "Invalid command!\n" ;

    }

    ExpressionTree expTree;
};

#endif // IEXPRESSIONTREE_H
