#ifndef RANDOMNODEGENERATOR_H
#define RANDOMNODEGENERATOR_H
#include "ExpressionNode.h"
#include "KnownOperators.h"
#include <map>

class RandomNodeGenerator
{
public:
    static AbstractExpressionNode* getRandomLeafOrNode(const std::map<const std::string, double>& variablesMap);
    static AbstractExpressionNode* getRandomNode();
    static AbstractExpressionNode* getRandomLeaf(const std::map<const std::string, double>& variablesMap);
private:
    static const std::string& getRandomOperator1Arg();
    static const std::string& getRandomOperator2Args();
    static AbstractExpressionNode* getRandomVariable(const std::map<const std::string, double> &variablesMap);
    static AbstractExpressionNode* fillNode(AbstractExpressionNode* nodeToFill, const std::map<const std::string, double>& variablesMap);

};

#endif // RANDOMNODEGENERATOR_H
