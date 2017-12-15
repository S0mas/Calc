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
    ExpressionTree(ExpressionTree&& other);
    ~ExpressionTree();

    void operator=(const ExpressionTree& other);
    void operator=(ExpressionTree&& other);
    void swap(ExpressionTree& left, ExpressionTree& right);
    void createTree(const std::vector<std::string>& strVec);
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
    std::map<const std::string, double> variablesMap;

    void toStringVecRec(const AbstractExpressionNode* root, std::vector<std::string>& strVec) const;
    void toStringRec(const AbstractExpressionNode* root, std::string& str) const;
    std::vector<AbstractExpressionNode*> translateStringVecToExpVec(const std::vector<std::string>& strVec) const;
    AbstractExpressionNode* getExpNode(const std::string& str) const;
    AbstractExpressionNode* getFulfillConstant() const;

    void clearTree();
    std::map<const std::string, double> getVariablesMap() const;
    void fillVariablesMap();
    void fillVariablesMapRec(const AbstractExpressionNode* root);
    void updateVarsValues(const std::vector<double>& variableValues);
    void updateVarsValuesRec(AbstractExpressionNode* root);

    AbstractExpressionNode*** getRandomNode();
    void getRandomNodeRec(AbstractExpressionNode** root, unsigned& nodeNumber, AbstractExpressionNode ***randomNode);
    void changeRandomNodeToRandomLeaf();
    AbstractExpressionNode* createNode(std::vector<std::string>::const_iterator &it, const std::vector<std::string>::const_iterator &end) const;

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
            for(auto& child : root->getChilds())
                getTreeSizeRec(child, size);
        }
    }
public:
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
