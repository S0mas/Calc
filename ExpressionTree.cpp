#include "ExpressionTree.h"

ExpressionTree::ExpressionTree(const ExpressionTree& other) : root(nullptr)
{
    createExpTree(other.toStringVec());
}


ExpressionTree::~ExpressionTree()
{
    clearTree();
}



void ExpressionTree::operator=(const ExpressionTree& other)
{
    clearTree();
    createExpTree(other.toStringVec());
}



void ExpressionTree::createExpTree(const std::vector<std::string>& strVec)
{
    std::vector<AbstractExpressionNode*> expVec = translateStringVecToExpVec(strVec);
    createExpTreeRec(&root, expVec);
    storeVariables();
}



void ExpressionTree::setVariablesValues(const std::vector<double>& valuesVec)
{
    if(valuesVec.size() == variablesMap.size())
    {
        std::vector<double>::const_iterator it = valuesVec.begin();
        for(auto& pair : variablesMap)
            pair.second = *it++;

        updateVariablesValuesInExpTree();
    }
}



void ExpressionTree::clearTree()
{
    if(root)
        delete root;
    variablesMap.clear();
}



unsigned int ExpressionTree::getNumberOfVariables() const
{
    return variablesMap.size();
}



ExpressionTree ExpressionTree::operator+(const ExpressionTree& other) const
{
    ExpressionTree expTree;
    std::vector<std::string> combinedStrVec;

    combinedStrVec = toStringVec();
    combinedStrVec.pop_back();
    combinedStrVec.insert( combinedStrVec.end(), other.toStringVec().begin(), other.toStringVec().end());

    expTree.createExpTree(combinedStrVec);
    return expTree;
}



void ExpressionTree::showTree() const
{
    if(root)
        showTreeRec(root);
}



void ExpressionTree::showVariables() const
{
    for(auto& var : variablesMap)
        std::cout << var.first << ": " << var.second << std::endl;
}



void ExpressionTree::calculate() const
{
    std::cout << "Result: " << root->getValue() << std::endl;
}



std::vector<std::string> ExpressionTree::toStringVec() const
{
    std::vector<std::string> strVec;
    toStringVecRec(root, strVec);
    return strVec;
}



void ExpressionTree::toStringVecRec(const AbstractExpressionNode* root, std::vector<std::string>& strVec) const
{
    strVec.push_back(root->toString());
    for(auto& child : root->childs)
        toStringVecRec(child, strVec);
}



std::vector<AbstractExpressionNode*> ExpressionTree::translateStringVecToExpVec(const std::vector<std::string>& strVec) const
{
    std::vector<AbstractExpressionNode*> expVec;
    for(auto& str : strVec)
        expVec.push_back(getExpNode(str));
    return expVec;
}



AbstractExpressionNode*ExpressionTree::getExpNode(const std::string& str) const
{
    AbstractExpressionNode* result = nullptr;
    if(str == "*" || str == "/" || str == "+" || str == "-")
        result = new Operator2Arg(str);
    else if(str == "sin" || str == "cos")
        result = new Operator1Arg(str);
    else if(Helper::constainsOnlyNumbers(str))
        result = new Constant(std::stod(str));
    else if(Helper::constainsOnlyLettersOrNumbers(str))
        result = new Variable(str);

    return result;
}



AbstractExpressionNode* ExpressionTree::getFulfillConstans() const
{
    return new Constant(1);
}



void ExpressionTree::showTreeRec(const AbstractExpressionNode* root) const
{
    if(root)
    {
        root->show();
        for(const AbstractExpressionNode* child : root->childs)
            showTreeRec(child);
    }
}



void ExpressionTree::createExpTreeRec(AbstractExpressionNode** root, std::vector<AbstractExpressionNode*>& expVec)
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



void ExpressionTree::updateVariablesValuesInExpTree()
{
    updateVariablesValuesInExpTreeRec(root);
}



void ExpressionTree::updateVariablesValuesInExpTreeRec(AbstractExpressionNode* root)
{
    if(typeid(*root) == typeid(Variable))
        dynamic_cast<Variable*>(root)->setValue(variablesMap[dynamic_cast<Variable*>(root)->getName()]);

    for(auto& child : root->childs)
        updateVariablesValuesInExpTreeRec(child);
}



void ExpressionTree::storeVariables()
{
    storeVariablesRec(root);
}



void ExpressionTree::storeVariablesRec(const AbstractExpressionNode* root)
{
    if(typeid(*root) == typeid(Variable))
        variablesMap.insert(std::make_pair<std::string, double>(dynamic_cast<const Variable*>(root)->getName(), dynamic_cast<const Variable*>(root)->getValue()));

    for(auto& child : root->childs)
        storeVariablesRec(child);
}
