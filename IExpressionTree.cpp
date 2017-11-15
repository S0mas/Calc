#include "IExpressionTree.h"

void IExpressionTree::run()
{
    while(true)
    {
        std::vector<std::string> command(Helper::splitString(getCommand()));
        processCommand(command);
    }
}

std::string IExpressionTree::getCommand() const
{
    std::string str;

    std::getline(std::cin, str);
    return str;
}

void IExpressionTree::processCommand(std::vector<std::string>& strVec)
{
    const std::string command = strVec.front();
    //Proceed with arguments only
    strVec.erase(strVec.begin());

    if(command == "enter")
        cmdValidator.validateComandEnterOrJoin(strVec) ? commandEnter(strVec) : logger.printError(ErrorsMsg::unrecognizedSymbol);
    else if(command == "join")
        cmdValidator.validateComandEnterOrJoin(strVec) ? commandJoin(strVec) : logger.printError(ErrorsMsg::unrecognizedSymbol);
    else if(command == "print")
        cmdValidator.validateComandVarsOrPrint(strVec) ? commandPrint() : logger.printError(ErrorsMsg::invalidArgsNumber);
    else if(command == "vars")
        cmdValidator.validateComandVarsOrPrint(strVec) ? commandVars() : logger.printError(ErrorsMsg::invalidArgsNumber);
    else if(command == "comp")
    {
        if(cmdValidator.validateComandCompTreeExist(expTree.toStringVec()))
        {
            //comp version with arguments
            if(!strVec.empty())
            {
                if(cmdValidator.validateComandCompArgsNumber(strVec, expTree.getNumberOfVariables()))
                {
                    if(cmdValidator.validateComandCompArgs(strVec))
                        commandComp(strVec);
                    else
                        logger.printError(ErrorsMsg::invalidValue);
                }
                else
                    logger.printError(ErrorsMsg::invalidArgsNumber);
            }
            else
                commandComp(strVec);
        }
        else
            logger.printError(ErrorsMsg::noExpression);
    }
    else if(command == "help")
        commandHelp();
    else
        logger.printError(ErrorsMsg::invalidCommand);
}

void IExpressionTree::commandEnter(const std::vector<std::string>& strVec)
{
    expTree.createExpTree(strVec);
    wasExprFixed(strVec, expTree.toStringVec());
    commandPrint();
}

void IExpressionTree::commandJoin(const std::vector<std::string>& strVec)
{
    ExpressionTree tempTree;
    tempTree.createExpTree(strVec);
    wasExprFixed(strVec, tempTree.toStringVec());
    expTree = expTree + tempTree;
    commandPrint();
}

void IExpressionTree::commandComp(const std::vector<std::string>& strVec)
{
    std::vector<int> valuesVec;
    std::transform(strVec.begin(), strVec.end(), std::back_inserter(valuesVec),
                   [](const std::string& str) { return std::stoi(str); });
    if(!valuesVec.empty())
        expTree.setVariablesValues(valuesVec);
    logger.printInfo(std::to_string(expTree.getResult()));
}

void IExpressionTree::commandPrint() const
{
    std::string expression("");
    for(auto& str : expTree.toStringVec())
        expression += str + " ";

    if(expression == "")
        expression = "No expression to print.";
    logger.printInfo(expression);
}

void IExpressionTree::commandVars() const
{
    logger.printInfo(expTree.variablesToString());
}

void IExpressionTree::commandHelp() const
{
    logger.printNormal("Options:\n"
                     "enter <expression> - to create expression ex. + 5 5, only unsigned int values and operators: +, -, *, /, sin, cos are valid.\n"
                     "join <expression> - to join any expression to existing one, last node from old expression will be lost.\n"
                     "comp - calculate value of expression with defined variabls values \n"
                     "comp <arg1> <arg2> ... <argn> also define variables values (same order as in vars command)\n"
                     "print - print actual expression\n"
                     "vars - show actual expression variables and theirs values\n"
                     "help - show this menu\n");
}

void IExpressionTree::wasExprFixed(const std::vector<std::string> &input, const std::vector<std::string> &output) const
{
    if(input.size() > output.size())
        logger.printWarning("Expression was fixed by removing of invalid part.");
    else if(input.size() < output.size())
        logger.printWarning("Expression was fixed by adding some '1' values.");
}
