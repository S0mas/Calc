#include "RandomNodeGenerator.h"

const std::string& RandomNodeGenerator::getRandomOperator1Arg()
{
    const std::vector<std::string>& operators = KnownOperators::getKnownOperators()->getOperators1Arg();
    return operators[Helper::getRandomNumber()%operators.size()];
}

const std::string& RandomNodeGenerator::getRandomOperator2Args()
{
    const std::vector<std::string>& operators = KnownOperators::getKnownOperators()->getOperators2Args();
    return operators[Helper::getRandomNumber()%operators.size()];
}

AbstractExpressionNode* RandomNodeGenerator::getRandomVariable(const std::map<std::string, double>& variablesMap)
{
    if(variablesMap.empty())
        return new Constant(Helper::getRandomNumber());

    unsigned position = Helper::getRandomNumber() % variablesMap.size();
    unsigned i = 0;

    for(auto& pair : variablesMap)
    {
        if(i==position)
            return new Variable(pair.first, pair.second);
    }
    return nullptr;//cant reach
}

AbstractExpressionNode* RandomNodeGenerator::fillNode(AbstractExpressionNode* nodeToFill, const std::map<std::string, double>& variablesMap)
{
    for(auto& child : nodeToFill->childs)
        child = getRandomLeaf(variablesMap);
    return nodeToFill;
}

AbstractExpressionNode* RandomNodeGenerator::getRandomNode()
{
    if(Helper::getRandomNumber()%2)
        return new Operator1Arg(getRandomOperator1Arg());
    return new Operator2Arg(getRandomOperator2Args());
}

AbstractExpressionNode* RandomNodeGenerator::getRandomLeaf(const std::map<std::string, double>& variablesMap)
{
    if(Helper::getRandomNumber()%2)
        return new Constant(Helper::getRandomNumber());
    return getRandomVariable(variablesMap);
}

AbstractExpressionNode* RandomNodeGenerator::getRandomLeafOrNode(const std::map<std::string, double> &variablesMap)
{
    if(Helper::getRandomNumber()%2)
       return fillNode(getRandomNode(), variablesMap);
    return getRandomLeaf(variablesMap);
}
