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
    std::string toString() const;
    void mutate();
    unsigned getTreeSize() const;
private:
    AbstractExpressionNode* root;
    std::map<std::string, double> variablesMap;

    void toStringVecRec(const AbstractExpressionNode* root, std::vector<std::string>& strVec) const;
    void toStringRec(const AbstractExpressionNode* root, std::string& str) const;
    std::vector<AbstractExpressionNode*> translateStringVecToExpVec(const std::vector<std::string>& strVec) const;
    AbstractExpressionNode* getExpNode(const std::string& str) const;
    AbstractExpressionNode* getFulfillConstans() const;

    void clearTree();
    void createExpTreeRec(AbstractExpressionNode** root, std::vector<AbstractExpressionNode*>& expVec);
    void updateVariablesValuesInExpTree();
    void updateVariablesValuesInExpTreeRec(AbstractExpressionNode* root);
    void storeVariables();
    void storeVariablesRec(const AbstractExpressionNode* root); 

    AbstractExpressionNode*** getRandomNode();
    void getRandomNodeRec(AbstractExpressionNode** root, int& nodeNumber, AbstractExpressionNode ***randomNode);
    void changeRandomNodeToRandomLeaf();

    static void swapNodes(AbstractExpressionNode*** nodeA, AbstractExpressionNode*** nodeB)
    {
        AbstractExpressionNode* temp = **nodeA;
        **nodeA = **nodeB;
        **nodeB = temp;
    }


    static void getTreeSizeRec(const AbstractExpressionNode* root, unsigned& size)
    {
        if(root)
        {
            ++size;
            for(auto& child : root->childs)
                getTreeSizeRec(child, size);
        }
    }
public:
    void setVariablesMap(const std::map<std::string, double>& newVarMap)
    {
        variablesMap = newVarMap;
    }

    static void crossOver(ExpressionTree &expTreeA,  ExpressionTree &expTreeB)
    {
        bool crossed = false;

        while(!crossed)
        {
            unsigned sizeOfNodeA = 0;
            unsigned sizeOfNodeB = 0;
            AbstractExpressionNode*** randA = expTreeA.getRandomNode();
            AbstractExpressionNode*** randB = expTreeB.getRandomNode();
            getTreeSizeRec(**randA, sizeOfNodeA);
            getTreeSizeRec(**randB, sizeOfNodeB);

            if(sizeOfNodeA < 7 && sizeOfNodeB < 7)
            {
                swapNodes(randA, randB);
                crossed = true;
            }

            delete randA;
            delete randB;
        }
    }
};

#endif //EXPRESSIONTREE_H
