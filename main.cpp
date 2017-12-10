#include <QCoreApplication>
#include "IExpressionTree.h"
#include "Logger.h"
#include "GeneticAlgorithm.h"
#include <unistd.h>
#include <fstream>

bool Logger::debugPrintsOn;

void writeResult(const GeneticAlgorithm::Result& result, const std::string& setup)
{
    std::ofstream file;

    file.open("C://Users//Somaso//Desktop//List3ZMPO//results.txt", std::ios_base::app);

    std::string res = setup + " Result: " + std::to_string(result.value) + " Expression: " + result.expression + "\n";
    file << res;

    file.close();
}
int main(int argc, char *argv[])
{
    std::srand(time(0));
    sleep(4);
    QCoreApplication a(argc, argv);
    //IExpressionTree calcTree;
    //calcTree.run();
    GeneticAlgorithm genAlg;
    GeneticAlgorithm::Result result;
    while(true)
    {
        result = genAlg.process(50, 300, 20, 10);
        if(result.value < 0.01)
            writeResult(result, "Setup:1");

        result = genAlg.process(70, 450, 25, 20);
        if(result.value < 0.01)
            writeResult(result, "Setup:2");

        result = genAlg.process(30, 900, 10, 5);
        if(result.value < 0.01)
            writeResult(result, "Setup:3");

        result = genAlg.process(100, 300, 10, 15);
        if(result.value < 0.01)
            writeResult(result, "Setup:4");

        result = genAlg.process(40, 600, 30, 8);
        if(result.value < 0.01)
            writeResult(result, "Setup:5");

        result = genAlg.process(28, 1200, 20, 15);
        if(result.value < 0.01)
            writeResult(result, "Setup:6");

        result = genAlg.process(20, 1500, 15, 8);
        if(result.value < 0.01)
            writeResult(result, "Setup:7");

        result = genAlg.process(60, 400, 30, 20);
        if(result.value < 0.01)
            writeResult(result, "Setup:8");

        result = genAlg.process(120, 500, 5, 15);
        if(result.value < 0.01)
            writeResult(result, "Setup:9");

        result = genAlg.process(60, 600, 8, 16);
        if(result.value < 0.01)
            writeResult(result, "Setup:10");
    }

    return a.exec();
}
