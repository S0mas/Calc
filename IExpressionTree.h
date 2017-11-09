#ifndef IEXPRESSIONTREE_H
#define IEXPRESSIONTREE_H
#include <string>
#include <vector>
#include <iostream>
#include "ExpressionTree.h"

class IExpressionTree
{
public:
    IExpressionTree();
    void makeTree()
    {
        std::string str;
        std::vector<std::string> strVec;

        while(std::cin >> str)
        {
            if(str == "GO")
                break;
            strVec.push_back(str);
        }
        ExpressionTree calcTree;
        calcTree.createExpTree(strVec);
        calcTree.calculate();

        return;
    }
};

#endif // IEXPRESSIONTREE_H
