#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include <vector>
#include <algorithm>
#include "ExpressionNode.h"

class ExpressionTree
{
public:
    ExpressionTree() : root(nullptr) {}

    void constructExpressionTree(AbstractExpressionNode** root)
    {
        if(exprVec.empty())
            return;

        *root = *exprVec.begin();
        exprVec.erase(exprVec.begin());

        //(*root)->show();

        if((*root)->exprType == operator1Arg)
        {
            constructExpressionTree(&dynamic_cast<Operator1Arg*>(*root)->child);
        }
        else if((*root)->exprType == operator2Arg)
        {
            constructExpressionTree(&dynamic_cast<Operator2Arg*>(*root)->leftChild);
            constructExpressionTree(&dynamic_cast<Operator2Arg*>(*root)->rightChild);
        }

    }

    void makeData()
    {
        std::string str;
        std::vector<std::string> strVec;

        while(std::cin >> str)
        {
            if(str == "GO")
                break;
            strVec.push_back(str);
        }

        while(!strVec.empty())
        {
            exprVec.push_back(getExpression(strVec.back()));
            strVec.pop_back();
        }

        std::reverse(exprVec.begin(),exprVec.end());

        return;
    }

//    void showTree(AbstractExpressionNode* root)
//    {
//        if(root)
//        {
//            if(root->exprType == constOrVariable)
//            {
//                std::cout << dynamic_cast<Constant*>(root)->getValue() << std::endl;
//            }
//            else if(root->exprType == operator1Arg)
//            {
//                std::cout << dynamic_cast<Operator1Arg*>(root)->type << std::endl;
//                showTree(dynamic_cast<Operator1Arg*>(root)->child);
//            }
//            else if(root->exprType == operator2Arg)
//            {
//                std::cout << dynamic_cast<Operator2Arg*>(root)->type << std::endl;
//                showTree(dynamic_cast<Operator2Arg*>(root)->leftChild);
//                showTree(dynamic_cast<Operator2Arg*>(root)->rightChild);
//            }
//        }
//    }

    void calculate()
    {
        std::cout << "Result: " << root->getValue() << std::endl;
    }

    AbstractExpressionNode* root;
    std::vector<AbstractExpressionNode*> exprVec;
private:
    AbstractExpressionNode* getExpression(const std::string& str) const
    {
        AbstractExpressionNode* result = nullptr;
        if(str == "*" || str == "/" || str == "+" || str == "-")
            result = new Operator2Arg(str);
        else if(str == "sin" || str == "cos")
            result = new Operator1Arg(str);
        else if(str == "sin" || str == "cos")
            result = new Operator1Arg(str);
        else if(Helper::constainsOnlyNumbers(str))
            result = new Constant(std::stoi(str));
        else if(Helper::constainsOnlyLettersOrNumbers(str))
            result = new Variable(str);

        return result;
    }
};

#endif //EXPRESSIONTREE_H
