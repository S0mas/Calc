#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <iostream>
#include "Helper.h"
#include <vector>

class AbstractExpressionNode
{
public:
    AbstractExpressionNode() {}

    virtual ~AbstractExpressionNode()
    {
        for(auto& child : childs)
            if(child) delete child;
    }
    virtual double getValue() const = 0;
    virtual std::string toString() const = 0;
    virtual void show() const = 0;

    std::vector<AbstractExpressionNode*> childs;
};

//No childs
class Constant : public AbstractExpressionNode
{
public:
    Constant(const double& value)
        :  value(value) {}

    virtual ~Constant() {}

    virtual double getValue() const override            { return value; }
    virtual std::string toString() const override       { return std::to_string(value) ; }
    virtual void show() const override                  { std::cout << value << std::endl; }

private:
    const double value;
};

//No childs
class Variable : public AbstractExpressionNode
{
public:
    Variable(const std::string& name)
        :  name(name), value(1) {}

    virtual ~Variable() {}

    virtual double getValue() const override            { return value; }
    virtual std::string toString() const override       { return name; }
    virtual void show() const override                  { std::cout << name << ": " << value << std::endl; }
    std::string getName() const                         { return name; }
    void setValue(const double& newValue)               { value = newValue; }

private:
    const std::string name;
    double value;
};


class AbstractOperatorNode : public AbstractExpressionNode
{
public:
    AbstractOperatorNode(const std::string& type)
        : type(type) {}

    virtual ~AbstractOperatorNode() {}
    virtual std::string toString() const override       { return type; }
    virtual void show() const override                  { std::cout << type << std::endl; }

    const std::string type;
};

//1 child
class Operator1Arg : public AbstractOperatorNode
{
public:
    Operator1Arg(const std::string& type) :
        AbstractOperatorNode(type)
    {
        childs.push_back(nullptr);
    }
    virtual ~Operator1Arg() {}

    virtual double getValue() const override            { return Helper::getFunction1Arg(type)(childs[0]->getValue()); }
};

//2 childs
class Operator2Arg : public AbstractOperatorNode
{
public:
    Operator2Arg(const std::string& type)
       : AbstractOperatorNode(type)
    {
        childs.push_back(nullptr);
        childs.push_back(nullptr);
    }
    virtual ~Operator2Arg() {}

    virtual double getValue() const override            { return Helper::getFunction2Arg(type)(childs[0]->getValue(), childs[1]->getValue()); }
};
#endif // EXPRESSIONNODE_H
