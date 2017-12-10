#ifndef RANDOMTREEGENERATOR_H
#define RANDOMTREEGENERATOR_H

#include "ExpressionTree.h"

class RandomTreeGenerator
{
public:
    static ExpressionTree&& generateRandomTree(const unsigned& varsNumber, const unsigned& minNodesNumber, const unsigned& maxNodesNumber);
private:
    static void generateRandomTreeRec(AbstractExpressionNode** root, const std::map<std::string, double>& variablesMap, unsigned& nodesNumber);
    static const std::map<std::string, double>&& generateVariablesMap(const unsigned &varsNumber);
};

#endif // RANDOMTREEGENERATOR_H
