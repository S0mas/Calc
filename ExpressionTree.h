#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <algorithm>
#include <map>
#include <typeinfo>
#include "RandomNodeGenerator.h"

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
    std::string variablesToString() const;
    double getResult() const;
    unsigned int getNumberOfVariables() const;
    std::vector<std::string> toStringVec() const;
    AbstractExpressionNode*** getRandomNode();
    void mutate();
    std::vector<ExpressionTree> crossOver(ExpressionTree &other) const;
private:
    AbstractExpressionNode* root;
    std::map<std::string, int> variablesMap;
    RandomNodeGenerator randNodeGen;

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

    unsigned getTreeSize() const;
    void getTreeSizeRec(const AbstractExpressionNode* root, unsigned& size) const;

    void showAddresses() const;
    void showAddressesRec(const AbstractExpressionNode* root) const;

    void swapNodes(AbstractExpressionNode*** nodeA, AbstractExpressionNode*** nodeB) const;
    void getRandomNodeRec(AbstractExpressionNode** root, int& nodeNumber, AbstractExpressionNode ***randomNode);

    void showTree() const;
    void showTreeRec(const AbstractExpressionNode* root) const;
};

#endif //EXPRESSIONTREE_H
