#include "GeneticAlgorithm.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

GeneticAlgorithm::GeneticAlgorithm()
{

}

void GeneticAlgorithm::process(const unsigned &populationSize, const unsigned &iterationNumber, const unsigned &crossOverProb, const unsigned &mutateProb)
{
    loadDataFile();
    if(data.empty() || !checkData())
    {
        Logger::printError("Error while loading data or data is empty!");
        return;
    }

    std::vector<ExpressionTree> population;
    initiate(populationSize, population);
    for(unsigned i = 0; i < iterationNumber; ++i)
    {
        select(populationSize, population);
        crossOver(crossOverProb, population);
        mutate(mutateProb, population);
    }
}

void GeneticAlgorithm::loadDataFile()
{
    QFile file("C://Users//Somaso//Desktop//List3ZMPO//dane.txt");

    if (!file.open(QIODevice::ReadOnly))
    {
        Logger::printError("Opening file error!");
        return;
    }

    QTextStream in(&file);
    QRegExp rx("(\\;)");

    while (!in.atEnd())
    {
       QString line = in.readLine();
       QStringList list = line.split(rx);

       std::vector<double> valuesVec;

       foreach (const QString &str, list)
       {
           bool ok = false;
           valuesVec.push_back(str.toDouble(&ok));
           if(!ok)
           {
               qDebug() << str;
               Logger::printError("Error while casting to double!");
               return;
           }
       }
       data.push_back(valuesVec);
    }

    return;
}

bool GeneticAlgorithm::checkData()
{
    foreach(const std::vector<double> &vec, data)
    {
        if(vec.size() != data.front().size())
            return false;
    }
    return true;
}

void GeneticAlgorithm::initiate(const unsigned &populationSize, std::vector<ExpressionTree>& population)
{
    for(unsigned i = 0; i < populationSize; ++i)
        population.push_back(RandomTreeGenerator::generateRandomTree(2u, 1u, 6u));
}

void GeneticAlgorithm::select(const unsigned& populationSize, std::vector<ExpressionTree>& population)
{
    std::vector<ExpressionTree> newParents;
    for(unsigned i = 0; i < populationSize; ++i)
       newParents.push_back(selectBestFromRandTwo(population));
    population = newParents;
}

ExpressionTree GeneticAlgorithm::selectBestFromRandTwo(std::vector<ExpressionTree>& expTreesVec)
{
    unsigned rand1 = Helper::getRandomNumber()%expTreesVec.size();
    unsigned rand2 = Helper::getRandomNumber()%expTreesVec.size();

    return (evaluateTree(expTreesVec[rand1]) < evaluateTree(expTreesVec[rand2])) ? expTreesVec[rand1] : expTreesVec[rand2];
}

unsigned GeneticAlgorithm::evaluateTree(ExpressionTree &expTree)
{
    double evalTree = 0;
    foreach (const std::vector<double>& values, data)
    {
        std::vector<double> variablesValues(values.begin(), values.end()-1);
        double result = values.back();

        expTree.setVariablesValues(variablesValues);
        evalTree += pow(result - expTree.getResult(), 2);
    }
    return evalTree;
}

void GeneticAlgorithm::crossOver(const unsigned& crossOverProb, std::vector<ExpressionTree>& expTreesVec)
{
    std::vector<ExpressionTree> childrensPopulation;
    std::pair<ExpressionTree, ExpressionTree> expTreePair;
    while(!expTreesVec.empty())
    {
        expTreePair = withdrawTreesPair(expTreesVec);
        if(Helper::getRandomNumber()%101 < crossOverProb)
            crossOverTreesPair(expTreePair);
        childrensPopulation.push_back(expTreePair.first);
        childrensPopulation.push_back(expTreePair.second);
    }
    expTreesVec = childrensPopulation;
}

void GeneticAlgorithm::crossOverTreesPair(std::pair<ExpressionTree, ExpressionTree> &expTreesPair)
{
    ExpressionTree::crossOver(std::get<0>(expTreesPair), std::get<1>(expTreesPair));
}

std::pair<ExpressionTree, ExpressionTree> GeneticAlgorithm::withdrawTreesPair(std::vector<ExpressionTree> &expTreesVec)
{
    return std::make_pair(withdrawRandTree(expTreesVec), withdrawRandTree(expTreesVec));
}

ExpressionTree GeneticAlgorithm::withdrawRandTree(std::vector<ExpressionTree> &expTreesVec)
{
    unsigned rand = Helper::getRandomNumber()%expTreesVec.size();
    ExpressionTree randTree = expTreesVec[rand];
    expTreesVec.erase(expTreesVec.begin()+rand);

    return randTree;
}

void GeneticAlgorithm::mutate(const unsigned& mutateProb, std::vector<ExpressionTree>& expTreesVec)
{
    for(unsigned i = 0; i < expTreesVec.size(); ++i)
    {
        if(Helper::getRandomNumber()%101 < mutateProb)
            expTreesVec[i].mutate();
    }
}
