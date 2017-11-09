#include <QCoreApplication>
#include "ExpressionTree.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ExpressionTree calcTree;
    calcTree.makeData();
    calcTree.constructExpressionTree(&calcTree.root);
    calcTree.showTree(calcTree.root);
    calcTree.calculate();
    return a.exec();
}
