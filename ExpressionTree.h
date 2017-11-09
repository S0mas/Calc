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

    void showTree() const   { if(root) showTreeRec(root); }
    void createExpTree(const std::vector<std::string>& strVec)
    {
        std::vector<AbstractExpressionNode*> expVec = translateStringVecToExpVec(strVec);
        createExpTreeRec(&root, expVec);
    }

    void calculate()
    {
        std::cout << "Result: " << root->getValue() << std::endl;
    }

    AbstractExpressionNode* root;

private:
    std::map<std::string, double> variablesMap;
    AbstractExpressionNode* getExpNode(const std::string& str)
    {
        AbstractExpressionNode* result = nullptr;
        if(str == "*" || str == "/" || str == "+" || str == "-")
            result = new Operator2Arg(str);
        else if(str == "sin" || str == "cos")
            result = new Operator1Arg(str);
        else if(Helper::constainsOnlyNumbers(str))
            result = new Constant(std::stoi(str));
        else if(Helper::constainsOnlyLettersOrNumbers(str))
        {
            variablesMap.insert(std::pair<std::string, double>(str, 1));
            result = new Variable(str);
        }

        return result;
    }

    void showTreeRec(const AbstractExpressionNode* root) const
    {
        if(root)
        {
            root->show();
            for(const AbstractExpressionNode* child : root->childs)
                showTreeRec(child);
        }
    }

    void createExpTreeRec(AbstractExpressionNode** root, std::vector<AbstractExpressionNode*>& expVec)
    {
        if(!expVec.empty())
        {
            *root = expVec.front();
            expVec.erase(expVec.begin());
        }
        else
            *root = getFulfillConstans();

        for(auto& child : (*root)->childs)
            createExpTreeRec(&child, expVec);
    }

    AbstractExpressionNode* getFulfillConstans() const
    {
        return new Constant(1);
    }

    void setVariablesValues(const std::vector<double>& valuesVec)
    {
        if(valuesVec.size() == variablesMap.size())
        {
            std::vector<double>::const_iterator it = valuesVec.begin();
            for(auto& pair : variablesMap)
                pair.second = *it++;

            updateVariablesValuesInExpTree();
        }
    }

    void updateVariablesValuesInExpTree()
    {
        updateVariablesValuesInExpTreeRec(root);
    }

    void updateVariablesValuesInExpTreeRec(AbstractExpressionNode* root)
    {
        if(typeid(*root) == typeid(Variable))
            dynamic_cast<Variable*>(root)->setValue(variablesMap[dynamic_cast<Variable*>(root)->getName()]);

        for(auto& child : root->childs)
            updateVariablesValuesInExpTreeRec(child);
    }

    std::vector<AbstractExpressionNode*> translateStringVecToExpVec(const std::vector<std::string>& strVec)
    {
        std::vector<AbstractExpressionNode*> expVec;
        for(auto& str : strVec)
            expVec.push_back(getExpNode(str));
        return expVec;
    }
};

#endif //EXPRESSIONTREE_H
