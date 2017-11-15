#ifndef IEXPRESSIONTREE_H
#define IEXPRESSIONTREE_H
#include "ExpressionTree.h"
#include "CommandValidator.h"
#include "Logger.h"
#include "ErrorsMsg.h"

class IExpressionTree
{
public:
    IExpressionTree(){}
    void run();//infinite loop
private:
    std::string getCommand() const;

    void processCommand(std::vector<std::string>& strVec);
    void commandEnter(const std::vector<std::string> &strVec);
    void commandJoin(const std::vector<std::string>& strVec);
    void commandComp(const std::vector<std::string> &strVec);
    void commandPrint() const;
    void commandVars() const;
    void commandHelp() const;
    void wasExprFixed(const std::vector<std::string> &input, const std::vector<std::string> &output) const;

    ExpressionTree expTree;
    CommandValidator cmdValidator;
    Logger logger;
};

#endif // IEXPRESSIONTREE_H
