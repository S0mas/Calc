#include <QCoreApplication>
#include "IExpressionTree.h"
#include "Logger.h"
#include "GeneticAlgorithm.h"

bool Logger::debugPrintsOn;
int main(int argc, char *argv[])
{
    std::srand(time(0));
    QCoreApplication a(argc, argv);
    //IExpressionTree calcTree;
    //calcTree.run();
    GeneticAlgorithm genAlg;
    genAlg.process(100, 1000, 60, 5);
    return a.exec();
}
