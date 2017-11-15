#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <algorithm>
#include <map>
#include <typeinfo>
#include "ExpressionNode.h"

class ExpressionTree
{

public:
    ExpressionTree() : root(nullptr) {}
    ExpressionTree(const ExpressionTree& other);
    ~ExpressionTree();

    void operator=(const ExpressionTree& other);
    void operator=(ExpressionTree&& other);
    void createExpTree(const std::vector<std::string>& strVec);
    void setVariablesValues(const std::vector<int>& valuesVec);

    ExpressionTree operator+(const ExpressionTree& other) const;
    std::vector<std::string> toStringVec() const;
    std::string variablesToString() const;
    double getResult() const;
    unsigned int getNumberOfVariables() const;

private:
    AbstractExpressionNode* root;
    std::map<std::string, int> variablesMap;

    void toStringVecRec(const AbstractExpressionNode* root, std::vector<std::string>& strVec) const;
    std::vector<AbstractExpressionNode*> translateStringVecToExpVec(const std::vector<std::string>& strVec) const;
    AbstractExpressionNode* getExpNode(const std::string& str) const;
    AbstractExpressionNode* getFulfillConstans() const;

    void clearTree();
    void createExpTreeRec(AbstractExpressionNode** root, std::vector<AbstractExpressionNode*>& expVec);
    void updateVariablesValuesInExpTree();
    void updateVariablesValuesInExpTreeRec(AbstractExpressionNode* root);
    void storeVariables();
    void storeVariablesRec(const AbstractExpressionNode* root);
};

#endif //EXPRESSIONTREE_H
