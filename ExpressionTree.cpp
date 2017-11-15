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

void ExpressionTree::operator=(ExpressionTree&& other)
{
    clearTree();
    root = other.root;
    variablesMap = other.variablesMap;
    other.root = nullptr;
}

void ExpressionTree::createExpTree(const std::vector<std::string>& strVec)
{
    clearTree();
    std::vector<AbstractExpressionNode*> expVec = translateStringVecToExpVec(strVec);
    createExpTreeRec(&root, expVec);
    storeVariables();
}

void ExpressionTree::setVariablesValues(const std::vector<int> &valuesVec)
{
    if(valuesVec.size() == variablesMap.size())
    {
        std::vector<int>::const_iterator it = valuesVec.begin();
        for(auto& pair : variablesMap)
            pair.second = *it++;

        updateVariablesValuesInExpTree();
    }
}

unsigned int ExpressionTree::getNumberOfVariables() const
{
    return variablesMap.size();
}

ExpressionTree ExpressionTree::operator+(const ExpressionTree& other) const
{
    ExpressionTree expTree;
    std::vector<std::string> combinedStrVec;
    std::vector<std::string> otherStrVec(other.toStringVec());
    combinedStrVec = toStringVec();

    //Remove last expression node if there is no empty base expression
    if(!combinedStrVec.empty())
        combinedStrVec.pop_back();

    combinedStrVec.insert( combinedStrVec.end(), otherStrVec.begin(), otherStrVec.end());

    std::map<std::string, int> oldVariables = variablesMap;
    expTree.createExpTree(combinedStrVec);

    //Restore old variables that are still in use in new expression
    for(auto& oldPair : oldVariables)
        if(expTree.variablesMap.find(oldPair.first) != expTree.variablesMap.end())
            expTree.variablesMap[oldPair.first] = oldPair.second;
    expTree.updateVariablesValuesInExpTree();

    return expTree;
}

std::string ExpressionTree::variablesToString() const
{
    std::string vars("");
    if(variablesMap.empty())
        vars = "No variables., ";
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
        for(auto& child : root->childs)
            toStringVecRec(child, strVec);
    }
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

void ExpressionTree::clearTree()
{
    if(root)
    {
        delete root;
        root = nullptr;
    }
    variablesMap.clear();
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
    if(root)
    {
        if(typeid(*root) == typeid(Variable))
            dynamic_cast<Variable*>(root)->setValue(variablesMap[dynamic_cast<Variable*>(root)->getName()]);

        for(auto& child : root->childs)
            updateVariablesValuesInExpTreeRec(child);
    }
}

void ExpressionTree::storeVariables()
{
    storeVariablesRec(root);
}

void ExpressionTree::storeVariablesRec(const AbstractExpressionNode* root)
{
    if(root)
    {
        if(typeid(*root) == typeid(Variable))
            variablesMap.insert(std::make_pair<std::string, int>(dynamic_cast<const Variable*>(root)->getName(), dynamic_cast<const Variable*>(root)->getValue()));

        for(auto& child : root->childs)
            storeVariablesRec(child);
    }
}
