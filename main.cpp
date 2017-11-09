#include <QCoreApplication>
#include "IExpressionTree.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    IExpressionTree calcTree;
    calcTree.makeTree();
    return a.exec();
}
