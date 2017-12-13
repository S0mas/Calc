#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H
#include "Helper.h"
#include "KnownOperators.h"
#include "Logger.h"

class AbstractExpressionNode
{
public:
    AbstractExpressionNode() {}

    virtual ~AbstractExpressionNode()
    {
        Logger::printDebug("Deleted Node Address: " + Helper::converAddressToString(static_cast<const void*>(this)));
        for(auto& child : childs)
        {
            if(child)
            {
                delete child;
                child = nullptr;
            }
        }
    }
    virtual double getValue() const = 0;
    virtual std::string toString() const = 0;
    virtual std::string toStringTree() const = 0;

    std::vector<AbstractExpressionNode*> childs;
};

//No childs
class Constant : public AbstractExpressionNode
{
public:
    Constant(const double& value)
        :  value(value) {}

    virtual ~Constant() {Logger::printDebug("Deleting Constant: " + toString());}

    virtual double getValue() const override            { return value; }
    virtual std::string toString() const override       { return std::to_string(value) ; }
    virtual std::string toStringTree() const override   { return toString();}

private:
    const double value;
};

//No childs
class Variable : public AbstractExpressionNode
{
public:
    Variable(const std::string& name)
        :  name(name), value(1) {}
    Variable(const std::string& name, double value)
        :  name(name), value(value) {}

    virtual ~Variable() {Logger::printDebug("Deleting.. Variable: " + toString());}

    virtual double getValue() const override            { return value; }
    virtual std::string toString() const override       { return name; }
    virtual std::string toStringTree() const override   { return toString();}
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
    virtual ~Operator1Arg() {Logger::printDebug("Deleting. Operator1: " + toString());}

    virtual double getValue() const override            { return KnownOperators::getKnownOperators()->getFunction1Arg(type)(childs[0]->getValue()); }
    virtual std::string toStringTree() const override   { return toString() + " " + childs[0]->toStringTree();}
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
    virtual ~Operator2Arg() {Logger::printDebug("Deleting.. Operator2: " + toString());}

    virtual double getValue() const override            { return KnownOperators::getKnownOperators()->getFunction2Args(type)(childs[0]->getValue(), childs[1]->getValue()); }
    virtual std::string toStringTree() const override   { return toString() + " " + childs[0]->toStringTree() + " " + childs[1]->toStringTree();}
};

#endif // EXPRESSIONNODE_H
