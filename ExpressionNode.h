#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H
#include "Helper.h"
#include "KnownOperators.h"
#include "Logger.h"
#include <typeinfo>

class AbstractExpressionNode
{
public:
    AbstractExpressionNode() {}
    AbstractExpressionNode(const AbstractExpressionNode& other)
    {
        for(const AbstractExpressionNode* child : childs)
            delete child;
        childs.clear();
        for(const AbstractExpressionNode* child : other.childs)
            childs.push_back(child->getCopy());
    }

    virtual ~AbstractExpressionNode()
    {
        for(const AbstractExpressionNode*  child : childs)
        {
            if(child)
                delete child;
        }
        childs.clear();
    }

    virtual double getValue() const = 0;
    virtual std::vector<AbstractExpressionNode*> getChilds() const  { return childs;}
    virtual bool isVariable() const                                 { return false;}
    virtual std::string toString() const = 0;
    virtual std::string toStringTree() const = 0;
    virtual AbstractExpressionNode* getCopy() const = 0;
protected:
    std::vector<AbstractExpressionNode*> childs;
};

//No childs
class Constant : public AbstractExpressionNode
{
public:
    Constant(const double& value)
        :  value(value) {}

    Constant(const Constant& other)
        : AbstractExpressionNode(other), value(other.value){}

    virtual ~Constant()                                         { Logger::printDebug("Deleting Constant: " + toString()); }
    virtual double getValue() const override                    { return value; }
    virtual std::string toString() const override               { return std::to_string(value); }
    virtual std::string toStringTree() const override           { return toString();}
    virtual AbstractExpressionNode* getCopy() const override    { return new Constant(value); }
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
    Variable(const Variable& other)
        :  AbstractExpressionNode(other), name(other.name), value(other.value) {}

    virtual ~Variable()                                         { Logger::printDebug("Deleting.. Variable: " + toString()); }
    virtual double getValue() const override                    { return value; }
    virtual std::string toString() const override               { return name; }
    virtual std::string toStringTree() const override           { return toString();}
    std::string getName() const                                 { return name; }
    void setValue(const double& newValue)                       { value = newValue; }
    virtual bool isVariable() const override                    { return true;}
    virtual AbstractExpressionNode* getCopy() const override    { return new Variable(name, value); }
private:
    const std::string name;
    double value;
};


class AbstractOperatorNode : public AbstractExpressionNode
{
public:
    AbstractOperatorNode(const std::string& type) : type(type){}

    AbstractOperatorNode(const AbstractOperatorNode& other)
        : AbstractExpressionNode(other), type(other.type) {}

    virtual ~AbstractOperatorNode() {}
    virtual std::string toString() const override       { return type; }
    const std::string type;
};

//1 child
class Operator1Arg : public AbstractOperatorNode
{
public:
    Operator1Arg(const std::string& type, AbstractExpressionNode* arg1) :
        AbstractOperatorNode(type)
    {
        childs.push_back(arg1);
    }

    Operator1Arg(const Operator1Arg& other) :
        AbstractOperatorNode(other){}

    virtual ~Operator1Arg()                                     { Logger::printDebug("Deleting. Operator1: " + toString()); }
    virtual double getValue() const override                    { return KnownOperators::getKnownOperators()->getFunction1Arg(type)(childs[0]->getValue()); }
    virtual std::string toStringTree() const override           { return toString() + " " + childs[0]->toStringTree(); }
    virtual AbstractExpressionNode* getCopy() const override    { return new Operator1Arg(type, childs[0]); }
};

//2 childs
class Operator2Arg : public AbstractOperatorNode
{
public:
    Operator2Arg(const std::string& type, AbstractExpressionNode* arg1, AbstractExpressionNode* arg2)
       : AbstractOperatorNode(type)
    {
        childs.push_back(arg1);
        childs.push_back(arg2);
    }

    Operator2Arg(const Operator2Arg& other)
        : AbstractOperatorNode(other){}

    virtual ~Operator2Arg()                                     { Logger::printDebug("Deleting.. Operator2: " + toString()); }
    virtual double getValue() const override                    { return KnownOperators::getKnownOperators()->getFunction2Args(type)(childs[0]->getValue(), childs[1]->getValue()); }
    virtual std::string toStringTree() const override           { return toString() + " " + childs[0]->toStringTree() + " " + childs[1]->toStringTree();}
    virtual AbstractExpressionNode* getCopy() const override    { return new Operator2Arg(type, childs[0], childs[1]); }
};

#endif // EXPRESSIONNODE_H
