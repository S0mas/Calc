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

    file.open("D://studiaINF//List3i4ZMPO//results.txt", std::ios_base::app);

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
    setups.push_back(Setup(50, 50, 20, 10, 0));
    setups.push_back(Setup(50, 50, 15, 10, 1));
    setups.push_back(Setup(50, 50, 10, 10, 2));
    setups.push_back(Setup(50, 70, 25, 20, 3));
    setups.push_back(Setup(50, 70, 20, 15, 4));
    setups.push_back(Setup(50, 70, 15, 10, 5));
    setups.push_back(Setup(36, 60, 25, 20, 6));
    setups.push_back(Setup(36, 60, 20, 15, 7));
    setups.push_back(Setup(36, 60, 15, 10, 8));
    setups.push_back(Setup(40, 40, 20, 15, 9));
    while(!result.choosenOne)
    {
        for(auto& setup : setups)
        {
            try
            {
                result = genAlg.process(setup);
            }
            catch(...)
            {
               Logger::printError("Dividing by 0 removing population.");
               break;
            }

            if(result.value < 0.30)
            {
                writeResult(result, "Setup:" + setup.toString() + " ");

            }
            std::cout << "Setup: "<< setup.toString() << " Value:" << result.value << " Expression: " << result.expression << std::endl;
            if(result.choosenOne)
                break;
        }
    }
    return a.exec();
}
