#include <QCoreApplication>
#include "IExpressionTree.h"
#include "Logger.h"
#include "GeneticAlgorithm.h"
#include <unistd.h>
#include <fstream>
#include <time.h>
#include <cstdio>
#include <vector>

bool Logger::debugPrintsOn;

void writeResult(const GeneticAlgorithm::Result& result, const std::string& setup)
{
    std::ofstream file;

    file.open("D://userdata//ksommerf//Desktop//GeneticCalc//Calc//results.txt", std::ios_base::app);

    std::string res = setup + " Result: " + std::to_string(result.value) + " Expression: " + result.expression + "\n";
    file << res;

    file.close();
}
int main(int argc, char *argv[])
{
    qsrand(time(0));
    QCoreApplication a(argc, argv);
    //IExpressionTree calcTree;
    //calcTree.run();

    GeneticAlgorithm genAlg;
    GeneticAlgorithm::Result result;
    std::vector<Setup> setups;
    //setups.push_back(Setup(40, 50, 10, 5, 0));
    //setups.push_back(Setup(50, 50, 10, 5, 2));
    //setups.push_back(Setup(50, 50, 5, 5, 3));
    //setups.push_back(Setup(40, 40, 20, 15, 4));
    //setups.push_back(Setup(40, 40, 15, 10, 5));
    //setups.push_back(Setup(40, 40, 10, 5, 6));
    //setups.push_back(Setup(40, 40, 5, 5, 7));
    //setups.push_back(Setup(30, 30, 20, 15, 8));
    //setups.push_back(Setup(30, 30, 15, 10, 9));
    //setups.push_back(Setup(30, 30, 10, 5, 8));
    //setups.push_back(Setup(30, 30, 5, 5, 9));

    setups.push_back(Setup(46, 45, 10, 5, 1));
    long startSingle = clock();
    long startChoosenOne = clock();
    long startGoodOne = clock();
    std::cout<<"Start processing..";
    while(!result.choosenOne)
    {
        for(auto& setup : setups)
        {
            try
            {
                std::cout<<".";
                startSingle = clock();
                qsrand(time(0));
                result = genAlg.process(setup);
            }
            catch(...)
            {
               Logger::printDebug("Dividing by 0 removing population.");
               break;
            }
            if(result.value > 0.000001 && result.value < 0.30)
            {
                long stopGoodOne = clock();

                Logger::printInfo("GoodOne: " + setup.toString() + " " + result.toString());
                Logger::printInfo("Time:" + std::to_string(stopGoodOne-startGoodOne) + "ms (single: " + std::to_string(stopGoodOne - startSingle) + "ms)");
                writeResult(result, setup.toString() + " ");
                startGoodOne = clock();
            }
            else if(result.choosenOne)
            {
                Logger::printInfo("ChoosenOne: " + setup.toString() + " " + result.toString());
                break;
            }
        }
    }
    long stopChoosenOne = clock();
    Logger::printInfo("Time:" + std::to_string(stopChoosenOne-startChoosenOne) + "ms");
    return a.exec();
}
