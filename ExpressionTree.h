#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <algorithm>
#include <map>
#include <typeinfo>
#include "RandomNodeGenerator.h"

class ExpressionTree
{
friend class RandomTreeGenerator;
public:
    ExpressionTree() : root(nullptr) {}
    ExpressionTree(const ExpressionTree& other);
    ~ExpressionTree();

    void operator=(const ExpressionTree& other);
    void operator=(ExpressionTree&& other);
    void createExpTree(const std::vector<std::string>& strVec);
    void setVariablesValues(const std::vector<double>& valuesVec);

    ExpressionTree operator+(const ExpressionTree& other) const;
    std::string variablesToString() const;
    double getResult() const;
    unsigned int getNumberOfVariables() const;
    std::vector<std::string> toStringVec() const;

    void mutate();
private:
    AbstractExpressionNode* root;
    std::map<std::string, double> variablesMap;

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

    AbstractExpressionNode*** getRandomNode();
    void getRandomNodeRec(AbstractExpressionNode** root, int& nodeNumber, AbstractExpressionNode ***randomNode);

    void showTree() const;
    void showTreeRec(const AbstractExpressionNode* root) const;

    static void swapNodes(AbstractExpressionNode*** nodeA, AbstractExpressionNode*** nodeB)
    {
        AbstractExpressionNode* temp = **nodeA;
        **nodeA = **nodeB;
        **nodeB = temp;
    }

public:
    //Do not use, its a hack for random trees generation only
    void setVariablesMap(const std::map<std::string, double>& newVarMap)
    {
        variablesMap = newVarMap;
    }

    static void crossOver(ExpressionTree &expTreeA,  ExpressionTree &expTreeB)
    {
        AbstractExpressionNode*** randA = expTreeA.getRandomNode();
        AbstractExpressionNode*** randB = expTreeB.getRandomNode();
        swapNodes(randA, randB);
        delete randA;
        delete randB;
    }
};

#endif //EXPRESSIONTREE_H
