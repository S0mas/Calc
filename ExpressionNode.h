#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <iostream>
#include "Helper.h"

enum ExpressionType
{
    constOrVariable = 0,
    operator1Arg,
    operator2Arg,
    invalid
};

class AbstractExpressionNode
{
public:
    AbstractExpressionNode(ExpressionType exprType = invalid)
        : exprType(exprType), parent(nullptr)                               { std::cout << "expr\n"; }

    virtual ~AbstractExpressionNode() {}
    virtual double getValue() const = 0;
    virtual void setParent(AbstractExpressionNode* newParent)               { parent = newParent; }
    virtual void show() const = 0;
    const ExpressionType exprType;

    AbstractExpressionNode* parent;
};

class Constant : public AbstractExpressionNode
{
public:
    Constant(const int& value)
        : AbstractExpressionNode(constOrVariable), value(value)             { std::cout << "const\n"; }

    virtual ~Constant() {}

    virtual double getValue() const override                                { return value; }
    virtual void show() const override                                      { std::cout << value << std::endl; }

private:
    const double value;
};

class Variable : public AbstractExpressionNode
{
public:
    Variable(const std::string& name, const int& value)
        : AbstractExpressionNode(constOrVariable), name(name), value(value) {std::cout << "var\n";}
    Variable(const std::string& name)
        : AbstractExpressionNode(constOrVariable), name(name), value(1)     {std::cout << "var\n";}

    virtual ~Variable() {}

    virtual double getValue() const override                                { return value; }
    virtual void show() const override                                      { std::cout << name << ": " << value << std::endl; }
    std::string getName() const                                             { return name; }
    void setValue(const int& newValue)                                      { value = newValue; }

private:
    const std::string name;
    double value;
};

class AbstractOperatorNode : public AbstractExpressionNode
{
public:
    AbstractOperatorNode(const std::string& type, const ExpressionType& exprType)
        : AbstractExpressionNode(exprType), type(type)                      { std::cout << "op\n"; }

    virtual void show() const override                                      { std::cout << type << std::endl; }

    const std::string type;
};

class Operator1Arg : public AbstractOperatorNode
{
public:
    Operator1Arg(const std::string& type) :
        AbstractOperatorNode(type, operator1Arg), child(nullptr)            { std::cout << "op1\n"; }

    virtual double getValue() const override                                { return Helper::getFunction1Arg(type)(child->getValue()); }

    void setChild(AbstractExpressionNode* next)                             { child = next; }

    AbstractExpressionNode* child;
};

class Operator2Arg : public AbstractOperatorNode
{
public:
    Operator2Arg(const std::string& type)
       : AbstractOperatorNode(type, operator2Arg), leftChild(nullptr), rightChild(nullptr)
                                                                            { std::cout << "op2\n"; }

    virtual double getValue() const override                                { return Helper::getFunction2Arg(type)(leftChild->getValue(), rightChild->getValue()); }

    void setLeftChild(AbstractExpressionNode* next)                         { leftChild = next; }
    void setRightChild(AbstractExpressionNode* next)                        { rightChild = next; }

    AbstractExpressionNode* leftChild;
    AbstractExpressionNode* rightChild;
};
#endif // EXPRESSIONNODE_H
