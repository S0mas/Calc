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

    file.open("D://userdata//ksommerf//Desktop//Kalkulator2//results.txt", std::ios_base::app);

    std::string res = setup + " Result: " + std::to_string(result.value) + " Expression: " + result.expression + "\n";
    file << res;

    file.close();
}
int main(int argc, char *argv[])
{
    std::srand(time(0));
    sleep(1);
    QCoreApplication a(argc, argv);
    //IExpressionTree calcTree;
    //calcTree.run();
    GeneticAlgorithm genAlg;
    GeneticAlgorithm::Result result;
    std::vector<Setup> setups;
    setups.push_back(Setup(50, 160, 25, 25, 0));
    setups.push_back(Setup(50, 80, 25, 25, 1));
    setups.push_back(Setup(40, 100, 25, 25, 2));
    setups.push_back(Setup(40, 80, 25, 25, 3));
    setups.push_back(Setup(40, 90, 25, 25, 4));
    setups.push_back(Setup(60, 50, 40, 10, 5));
    setups.push_back(Setup(60, 40, 15, 10, 6));
    setups.push_back(Setup(60, 45, 10, 20, 7));
    setups.push_back(Setup(50, 40, 30, 30, 8));
    setups.push_back(Setup(50, 40, 40, 40, 9));
    while(true)
    {
        for(auto& setup : setups)
        {
            result = genAlg.process(setup);
            if(result.value < 0.01)
                writeResult(result, "Setup:1");
            std::cout << "Setup: "<< setup.id << " " << result.value << " Expression: " << result.expression << std::endl;
        }
    }

    return a.exec();
}
