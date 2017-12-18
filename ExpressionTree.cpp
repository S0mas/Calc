#include "ExpressionTree.h"
#include <iostream>

ExpressionTree::ExpressionTree(const ExpressionTree& other) : root(nullptr)
{
    clearTree();
    root = other.root->getCopy();
    fillVariablesMap();
}

//ExpressionTree::ExpressionTree(ExpressionTree&& other)
//{
//    swap(this, &other);
//    other.root = nullptr;
//}

ExpressionTree::~ExpressionTree()
{
    clearTree();
}

void ExpressionTree::operator=(const ExpressionTree& other)
{
    clearTree();
    root = other.root->getCopy();
    variablesMap = other.variablesMap;
}

//void ExpressionTree::operator=(ExpressionTree&& other)
//{
//    clearTree();
//    swap(this, &other);
//}

//void ExpressionTree::swap(ExpressionTree* left, ExpressionTree* right)
//{
//    AbstractExpressionNode* temp = left->root;
//    left->root = right->root;
//    right->root = temp;

//    std::map<const std::string, double> tempMap = left->variablesMap;
//    left->variablesMap = right->variablesMap;
//    right->variablesMap = tempMap;
//}

void ExpressionTree::setVariablesValues(const std::vector<double>& valuesVec)
{
    unsigned i = 0;
    for(auto& pair : variablesMap)
        pair.second = valuesVec[i++];

    updateVarsValuesRec(root);
}

unsigned int ExpressionTree::getNumberOfVariables() const
{
    return variablesMap.size();
}

ExpressionTree ExpressionTree::operator+(const ExpressionTree& other) const
{
    ExpressionTree expTree;
    expTree.root = this->root->getCopy();

    AbstractExpressionNode* lastNode = expTree.root;
    for(AbstractExpressionNode* child : expTree.root->getChilds())
        lastNode = child;

    delete lastNode;
    lastNode = nullptr;

    lastNode = other.root->getCopy();
    expTree.fillVariablesMap();

    return expTree;
}

std::string ExpressionTree::variablesToString() const
{
    std::string vars("");
    if(variablesMap.empty())
        vars = "No variables.  ";
    for(auto& var : variablesMap)
        vars += var.first + ": " + std::to_string(var.second) + ", ";

    //remove last 2 chars ", "
    vars.pop_back();
    vars.pop_back();
    return vars;
}

double ExpressionTree::getResult() const
{
    return root->getValue();
}

std::vector<std::string> ExpressionTree::toStringVec() const
{
    std::vector<std::string> strVec;
    toStringVecRec(root, strVec);
    return strVec;
}

void ExpressionTree::toStringVecRec(const AbstractExpressionNode* root, std::vector<std::string>& strVec) const
{
    if(root)
    {
        strVec.push_back(root->toString());
        for(auto& child : root->getChilds())
            toStringVecRec(child, strVec);
    }
}

std::string ExpressionTree::toString() const
{
    return root->toStringTree();
}

AbstractExpressionNode*** ExpressionTree::getRandomNode()
{
    AbstractExpressionNode*** randomNode = new AbstractExpressionNode**();
    AbstractExpressionNode** parent = new AbstractExpressionNode*();
    int nodeNumber = 0;
    std::cout << "TreeSize: " << getTreeSize() << std::endl;

    nodeNumber = Helper::getRandomNumber() % getTreeSize();
    getRandomNodeRec(&root, nodeNumber, randomNode, parent);

    std::cout << "Rand1 " << *randomNode << std::endl;
    std::cout << "Rand2 " << **randomNode << std::endl;
    std::cout << "Parent1 " << Helper::converAddressToString(parent) << std::endl;
    std::cout << "Parent2 " << Helper::converAddressToString(*parent) << std::endl;
    if(*parent)
    {
        for(auto& child : (*parent)->getChilds())
        {
            std::cout << "Childs" << std::endl;
            std::cout <<child->toAddressTree() <<std::endl;
        }
    }
    return randomNode;
}

void ExpressionTree::getRandomNodeRec(AbstractExpressionNode** xx, int& nodeNumber, AbstractExpressionNode*** randomNode, AbstractExpressionNode** parent)
{
    if(xx && nodeNumber >= 0)
    {
        if(nodeNumber == 0)
        {
            --nodeNumber;
            *randomNode = xx;
        }
        else
        {
            --nodeNumber;
            *parent = *xx;
            std::cout << "SetParent2 " << Helper::converAddressToString(*parent) << std::endl;
            for(auto& child : (*xx)->getChilds())
                getRandomNodeRec(&child, nodeNumber, randomNode, parent);

        }

    }
}

void ExpressionTree::mutate()
{
    std::cout <<"1" <<std::endl;
    AbstractExpressionNode*** randomNode = getRandomNode();

    std::cout <<"21" << Helper::converAddressToString(randomNode) << std::endl;
    std::cout <<"22" << Helper::converAddressToString(*randomNode) << std::endl;
    std::cout <<"23" << Helper::converAddressToString(**randomNode) << std::endl;
    delete **randomNode;
    **randomNode = nullptr;
    std::cout <<"3" <<std::endl;
    int mutationNodeOperatorsCount = Helper::getRandomNumber()%5;
    std::cout <<"4" <<std::endl;
    **randomNode = RandomNodeGenerator::getRandomTree(variablesMap, mutationNodeOperatorsCount);

    std::cout <<"\nNULL???" << Helper::converAddressToString(**randomNode) << std::endl;
    std::cout <<"\nCOTO" << (**randomNode)->toStringTree() << std::endl;
    std::cout <<"\n5" << (**randomNode)->toAddressTree() << std::endl;
    delete randomNode;
    std::cout <<"6" <<std::endl;
}

void ExpressionTree::createTree(const std::vector<std::string>& strVec)
{
    std::vector<std::string>::const_iterator it = strVec.begin();
    std::vector<std::string>::const_iterator end = strVec.end();
    clearTree();
    root = createNode(it, end);
}

AbstractExpressionNode* ExpressionTree::createNode(std::vector<std::string>::const_iterator& it, const std::vector<std::string>::const_iterator& end) const
{
    AbstractExpressionNode* result = nullptr;
    if(it != end)
    {
        const std::string& element =  *it;
        if(KnownOperators::getKnownOperators()->isOperator2Args(element))
            result = new Operator2Arg(element, createNode(++it, end), createNode(++it, end));
        else if(KnownOperators::getKnownOperators()->isOperator1Arg(element))
            result = new Operator1Arg(element, createNode(++it, end));
        else if(Helper::constainsOnlyNumbers(element))
            result = new Constant(std::stod(element));
        else if(Helper::constainsOnlyLettersOrNumbers(element))
            result = new Variable(element);
        ++it;
    }
    else
        result = getFulfillConstant();

    return result;
}

AbstractExpressionNode* ExpressionTree::getFulfillConstant() const
{
    return new Constant(1);
}

void ExpressionTree::clearTree()
{
    if(root)
    {
        delete root;
        root = nullptr;
    }
    variablesMap.clear();
}

std::map<const std::string, double> ExpressionTree::getVariablesMap() const
{
    return variablesMap;
}

void ExpressionTree::fillVariablesMap()
{
    fillVariablesMapRec(root);
}

void ExpressionTree::fillVariablesMapRec(const AbstractExpressionNode* root)
{
    variablesMap.clear();
    if(root)
    {
        if(root->isVariable())
        {
            const Variable* var = dynamic_cast<const Variable*>(root);
            variablesMap.insert(std::make_pair<const std::string, double>(var->getName(), var->getValue()));
        }
        for(const AbstractExpressionNode* child : root->getChilds())
            fillVariablesMapRec(child);
    }
}

void ExpressionTree::updateVarsValuesRec(AbstractExpressionNode* root)
{
    if(root)
    {
        if(root->isVariable())
        {
            Variable* var = dynamic_cast<Variable*>(root);
            var->setValue(variablesMap[var->getName()]);
        }

        for(AbstractExpressionNode* child : root->getChilds())
            updateVarsValuesRec(child);
    }
}


unsigned ExpressionTree::getTreeSize() const
{
    unsigned size = 0;
    getTreeSizeRec(root, size);
    return size;
}
