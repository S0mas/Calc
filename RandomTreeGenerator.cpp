#include "RandomTreeGenerator.h"

ExpressionTree RandomTreeGenerator::generateRandomTree(const unsigned& varsNumber, const unsigned& minNodesNumber, const unsigned& maxNodesNumber)
{
    ExpressionTree expTree;
    const std::map<const std::string, double>& variablesMap = generateVariablesMap(varsNumber);

    int nodesNumber = Helper::getRandomNumber()%(maxNodesNumber - minNodesNumber) + minNodesNumber;
    generateRandomTreeRec(&expTree.root, variablesMap, nodesNumber);
    expTree.fillVariablesMap();
    return expTree;
}

void RandomTreeGenerator::generateRandomTreeRec(AbstractExpressionNode **root, const std::map<const std::string, double>& variablesMap, int &nodesNumber)
{
    if(nodesNumber > 0)
        *root = RandomNodeGenerator::getRandomNode();
    else
        *root = RandomNodeGenerator::getRandomLeaf(variablesMap);
    --nodesNumber;
    for(auto& child : (*root)->getChilds())
        generateRandomTreeRec(&child, variablesMap, nodesNumber);
}

const std::map<const std::string, double> RandomTreeGenerator::generateVariablesMap(const unsigned& varsNumber)
{
    if(varsNumber > 26)
        Logger::printError("Too much variables! Max is 26.");
    std::map<const std::string, double> variablesMap;
    int charNumber = 65;
    for(int i = 0; i < varsNumber; ++i, ++charNumber)
    {
        char ch = static_cast<char>(charNumber);
        std::string firstLetter(1, ch);

        variablesMap.insert(std::make_pair(firstLetter, 0.0));
    }

    return variablesMap;
}
