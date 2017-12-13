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
    //std::srand(time(0));
    QCoreApplication a(argc, argv);
    //IExpressionTree calcTree;
    //calcTree.run();


    GeneticAlgorithm genAlg;
    GeneticAlgorithm::Result result;
    std::vector<Setup> setups;
    setups.push_back(Setup(50, 50, 20, 10, 0));
    setups.push_back(Setup(100, 100, 20, 10, 1));
//    setups.push_back(Setup(80, 50, 0, 0, 2));
//    setups.push_back(Setup(70, 40, 0, 0, 3));
//    setups.push_back(Setup(60, 30, 0, 0, 4));
//    setups.push_back(Setup(50, 20, 0, 0, 5));
//    setups.push_back(Setup(40, 50, 0, 0, 6));
//    setups.push_back(Setup(30, 40, 0, 0, 7));
//    setups.push_back(Setup(20, 30, 0, 0, 8));
//    setups.push_back(Setup(10, 20, 0, 0, 9));
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

            if(result.value < 0.1)
            {
                writeResult(result, "Setup:" + setup.id);

            }
            std::cout << "Setup: "<< setup.id << " MaxTreeSize:" << result.setupMaxTreeSize << " Value:" << result.value << " Expression: " << result.expression << std::endl;
            if(result.choosenOne)
                break;
        }
    }
    return a.exec();
}
