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
    //ExpressionTree(ExpressionTree&& other);
    ~ExpressionTree();

    void operator=(const ExpressionTree& other);
    //void operator=(ExpressionTree&& other);
    static void swap(ExpressionTree *left, ExpressionTree *right);
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
        AbstractExpressionNode* root;
private:

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
    void getRandomNodeRec(AbstractExpressionNode** root, int &nodeNumber, AbstractExpressionNode ***randomNode, AbstractExpressionNode **parent);
    AbstractExpressionNode* createNode(std::vector<std::string>::const_iterator &it, const std::vector<std::string>::const_iterator &end) const;

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
    static void crossOver(ExpressionTree &otherA, ExpressionTree &otherB)
    {
//        Logger::printError("crossA1:  " + otherA.root->toAddressTree());
//        Logger::printError("crossB1:  " + otherB.root->toAddressTree());

//        AbstractExpressionNode*** randA = otherA.getRandomNode();
//        AbstractExpressionNode*** randB = otherB.getRandomNode();
//        std::string a11 = Helper::converAddressToString(randA);
//        std::string a21 = Helper::converAddressToString(*randA);
//        std::string a31 = Helper::converAddressToString(**randA);
//        std::string b11 = Helper::converAddressToString(randB);
//        std::string b21 = Helper::converAddressToString(*randB);
//        std::string b31 = Helper::converAddressToString(**randB);

//        Logger::printError("----->inCrossA1:  " + (**randA)->toAddressTree());
//        Logger::printError("----->inCrossB1:  " + (**randB)->toAddressTree());

//        AbstractExpressionNode* temp = **randA;
//        **randA = **randB;
//        //**randB = temp;

//        std::string a12 = Helper::converAddressToString(randA);
//        std::string a22 = Helper::converAddressToString(*randA);
//        std::string a32 = Helper::converAddressToString(**randA);
//        std::string b12 = Helper::converAddressToString(randB);
//        std::string b22 = Helper::converAddressToString(*randB);
//        std::string b32 = Helper::converAddressToString(**randB);

//        Logger::printError("----->inCrossA2:  " + (**randA)->toAddressTree());
//        Logger::printError("----->inCrossB2:  " + (**randB)->toAddressTree());


//        Logger::printError("PrzedA3: "+a31);

//        Logger::printError("PrzedB3: "+b31);

//        Logger::printError("PoA3: "+a32);

//        Logger::printError("PoB3: "+b32);

//        Logger::printError("crossA2:  " + otherA.root->toAddressTree());
//        Logger::printError("crossB2:  " + otherB.root->toAddressTree());

//        delete randA;
//        delete randB;
    }
    static ExpressionTree generateRandomTree(const unsigned& varsNumber, const unsigned& minNodesNumber, const unsigned& maxNodesNumber)
    {
        ExpressionTree expTree;
        const std::map<const std::string, double>& variablesMap = RandomNodeGenerator::generateVariablesMap(varsNumber);
        int nodesNumber = Helper::getRandomNumber()%(maxNodesNumber - minNodesNumber) + minNodesNumber;

        expTree.root = RandomNodeGenerator::getRandomTree(variablesMap, nodesNumber);
        expTree.fillVariablesMap();

        std::cout <<"GeneratedTree: " << expTree.root->toAddressTree() << std::endl;
        return expTree;
    }
};

#endif //EXPRESSIONTREE_H
