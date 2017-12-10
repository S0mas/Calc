#ifndef RANDOMNODEGENERATOR_H
#define RANDOMNODEGENERATOR_H
#include "ExpressionNode.h"
#include "KnownOperators.h"
#include <map>

class RandomNodeGenerator
{
  public:
    RandomNodeGenerator(){}

    const std::string& getRandomOperator1Arg() const;
    const std::string& getRandomOperator2Args() const;
    AbstractExpressionNode* getRandomVariable(const std::map<std::string, int>& variablesMap) const;
    AbstractExpressionNode* fillNode(AbstractExpressionNode* nodeToFill, const std::map<std::string, int>& variablesMap) const;
    AbstractExpressionNode* getRandomNode() const;
    AbstractExpressionNode* getRandomLeaf(const std::map<std::string, int>& variablesMap) const;
    AbstractExpressionNode* getRandomLeafOrNode(const std::map<std::string, int>& variablesMap) const;
};

#endif // RANDOMNODEGENERATOR_H
