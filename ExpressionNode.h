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
    static std::vector<std::string> deletedAddresses;
    AbstractExpressionNode(const AbstractExpressionNode& other)
    {
        int a;
        std::cout<<" ABSTRACT!!!!!!!!!!!!DELETING \n";
        std::cin >> a;
        for(const AbstractExpressionNode* child : childs)
        {
            if(child)
            {
                delete child;
            }

        }
        std::cout<<" END!!!!!!!!!!!! \n";
        std::cin >> a;
        childs.clear();

        for(const AbstractExpressionNode* child : other.childs)
            childs.push_back(child->getCopy());
    }
    virtual ~AbstractExpressionNode(){}

    virtual double getValue() const = 0;
    virtual std::vector<AbstractExpressionNode*> getChilds() const  { return childs;}
    virtual bool isVariable() const                                 { return false;}
    virtual std::string toString() const = 0;
    virtual std::string toStringTree() const = 0;
    virtual std::string toAddressTree() const                       { return "ABSTRACT";}
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

    virtual ~Constant()                                         { std::cout<<" Constant "; }
    virtual double getValue() const override                    { return value; }
    virtual std::string toString() const override               { return std::to_string(value); }
    virtual std::string toStringTree() const override           { return toString();}
    virtual AbstractExpressionNode* getCopy() const override    { return new Constant(value); }
    virtual std::string toAddressTree() const  override         { return "Constant: " +Helper::converAddressToString(this);}
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

    virtual ~Variable()                                         { std::cout<<" Variable "; }
    virtual double getValue() const override                    { return value; }
    virtual std::string toString() const override               { return name; }
    virtual std::string toStringTree() const override           { return toString();}
    std::string getName() const                                 { return name; }
    void setValue(const double& newValue)                       { value = newValue; }
    virtual bool isVariable() const override                    { return true;}
    virtual AbstractExpressionNode* getCopy() const override    { return new Variable(name, value); }
    virtual std::string toAddressTree() const  override
    {
        return "Var: " +Helper::converAddressToString(this);}
private:
    const std::string name;
    double value;
};


class AbstractOperatorNode : public AbstractExpressionNode
{
public:
    AbstractOperatorNode(const std::string& type) : type(type){}

    AbstractOperatorNode(const AbstractOperatorNode& other)
        : AbstractExpressionNode(other), type(other.type) {
        int a;
        std::cout<<" AbstractOperatorNode \n";
        std::cin >> a;

    }

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
        AbstractOperatorNode(other){
        int a;
        std::cout<<" Operator1ArgCOPYCTR \n";
        std::cin >> a;
    }

    virtual ~Operator1Arg()
    {
        std::cout<<" 1ARG ";
        for(const AbstractExpressionNode*  child : childs)
        {
            if(child)
                delete child;
        }
        childs.clear();
    }
    virtual double getValue() const override                    { return KnownOperators::getKnownOperators()->getFunction1Arg(type)(childs[0]->getValue()); }
    virtual std::string toStringTree() const override           { return toString() + " " + childs[0]->toStringTree(); }
    virtual AbstractExpressionNode* getCopy() const override    { return new Operator1Arg(type, childs[0]->getCopy()); }
    virtual std::string toAddressTree() const  override         { return "Op1: " +Helper::converAddressToString(this) + " ---> " + childs[0]->toAddressTree();}
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
        : AbstractOperatorNode(other)
    {
        int a;
        std::cout<<" Operator2ArgCOPYCTR \n";
        std::cin >> a;
    }

    virtual ~Operator2Arg()
    {
         std::cout<<" 2ARG ";
        for(const AbstractExpressionNode*  child : childs)
        {
            if(child)
                delete child;
        }
        childs.clear();
    }
    virtual double getValue() const override                    { return KnownOperators::getKnownOperators()->getFunction2Args(type)(childs[0]->getValue(), childs[1]->getValue()); }
    virtual std::string toStringTree() const override           { return toString() + " " + childs[0]->toStringTree() + " " + childs[1]->toStringTree();}
    virtual AbstractExpressionNode* getCopy() const override    { return new Operator2Arg(type, childs[0]->getCopy(), childs[1]->getCopy()); }
    virtual std::string toAddressTree() const  override         { return "Op2: " +Helper::converAddressToString(this) + " ---> " + childs[0]->toAddressTree() + " ---> " + childs[1]->toAddressTree();}
};

#endif // EXPRESSIONNODE_H
