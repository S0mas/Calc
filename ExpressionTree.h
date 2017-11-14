#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <vector>
#include <algorithm>
#include <map>
#include "ExpressionNode.h"
#include <typeinfo>

class ExpressionTree
{

public:
    ExpressionTree() : root(nullptr) {}
    ExpressionTree(const ExpressionTree& other);
    ~ExpressionTree();

    void operator=(const ExpressionTree& other);
    void createExpTree(const std::vector<std::string>& strVec);
    void setVariablesValues(const std::vector<double>& valuesVec);
    void clearTree();

    ExpressionTree operator+(const ExpressionTree& other) const;
    void showTree() const;
    std::vector<std::string> toStringVec() const;
    void showVariables() const;
    void calculate() const;
    unsigned int getNumberOfVariables() const;

private:
    AbstractExpressionNode* root;
    std::map<std::string, double> variablesMap;

    void toStringVecRec(const AbstractExpressionNode* root, std::vector<std::string>& strVec) const;
    std::vector<AbstractExpressionNode*> translateStringVecToExpVec(const std::vector<std::string>& strVec) const;
    AbstractExpressionNode* getExpNode(const std::string& str) const;
    AbstractExpressionNode* getFulfillConstans() const;
    void showTreeRec(const AbstractExpressionNode* root) const;

    void createExpTreeRec(AbstractExpressionNode** root, std::vector<AbstractExpressionNode*>& expVec);
    void updateVariablesValuesInExpTree();
    void updateVariablesValuesInExpTreeRec(AbstractExpressionNode* root);
    void storeVariables();
    void storeVariablesRec(const AbstractExpressionNode* root);
};

#endif //EXPRESSIONTREE_H
