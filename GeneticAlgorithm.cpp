#include "GeneticAlgorithm.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <cmath>
#include <exception>

GeneticAlgorithm::GeneticAlgorithm()
{
    loadDataFile();
    if(dataValues.empty() || dataResults.empty() || dataValues.size() != dataResults.size())
    {
        Logger::printError("Error while loading data or data is empty!");
        return;
    }
}

GeneticAlgorithm::Result GeneticAlgorithm::process(const Setup& setup)
{
    Result result;
    bool foundChoosenOne = false;
    std::vector<ExpressionTree> population;
    population.reserve(setup.population*1.5);

    initiate(setup.population, population);
    if(!population.empty())
    {
        double selectTime = 0;
        double crossTime = 0;
        double muatateTime = 0;

        for(unsigned i = 0; i < setup.iteration; ++i)
        {
            foundChoosenOne = lookForGoldenChild(population, result);
            if(foundChoosenOne)
                break;
            clock_t p1 = clock();
            select(setup.population, population);
            clock_t p2 = clock();
            crossOver(setup.crossChance, population);
            clock_t p3 = clock();
            mutate(setup.mutationChance, population);
            clock_t p4 = clock();

            selectTime +=p2-p1;
            crossTime += p3-p2;
            muatateTime += p4-p3;
        }
        Logger::printInfo("Iteration:"+ std::to_string(setup.iteration) + " Times: Select|cross|mutate: "
                          + std::to_string(selectTime)+"|" +std::to_string(crossTime)+"|" +std::to_string(muatateTime));
        //Find best result
        if(!foundChoosenOne)
        {
            int bestId = 0;
            double bestResult = evaluateTree(population[bestId]);

            for(unsigned i = 1; i < population.size(); ++i)
            {
                double temp = evaluateTree(population[i]);
                if(temp < bestResult)
                    bestResult = temp;
                if(result.setupMaxTreeSize < population[i].getTreeSize())
                    result.setupMaxTreeSize = population[i].getTreeSize();
            }

            result.expression = population[bestId].toString();
            result.value = bestResult;
        }
    }
    else
        Logger::printError("Population is empty!");

    return result;
}

bool GeneticAlgorithm::lookForGoldenChild(std::vector<ExpressionTree>& population, Result& result)
{
    bool found = false;
    for(auto& tree : population)
    {
        double temp = evaluateTree(tree);
        if( temp < 0.000001)
        {
            Logger::printInfo("Found choosen one!");
            result.value = temp;
            result.expression = tree.toString();
            result.choosenOne = true;
            found = true;
            break;
        }
    }
    return found;
}

void GeneticAlgorithm::loadDataFile()
{
    QFile file("D://studiaINF//List3i4ZMPO//dane.txt");

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

       for(int i = 0; i < 3; ++i)
       {
           QString str = list[i];
           if(i%3 != 0)
               str.remove(0, 1);

           bool ok = false;
           if(i%3 != 2)
               valuesVec.push_back(str.toDouble(&ok));
           else
               dataResults.push_back(str.toDouble(&ok));

           if(!ok)
           {
               qDebug() << str;
               Logger::printError("Error while casting to double!");
               return;
           }
       }
       dataValues.push_back(valuesVec);
    }

    return;
}

void GeneticAlgorithm::initiate(const unsigned &populationSize, std::vector<ExpressionTree>& population)
{
    population.reserve(populationSize*1.5);
    for(unsigned i = 0; i < populationSize; ++i)
        population.push_back(RandomTreeGenerator::generateRandomTree(2, 1, 3));
}

void GeneticAlgorithm::select(const unsigned& populationSize, std::vector<ExpressionTree>& population)
{
    unsigned maxTreeSize = 0;
    std::vector<ExpressionTree> newParents;
    newParents.reserve(populationSize*1.5);
    //clock_t p1 = clock();
    for(unsigned i = 0; i < populationSize; ++i)
    {
       //clock_t p1 = clock();
       newParents.push_back(selectBestFromRandTwo(population));
       if(maxTreeSize < newParents.back().getTreeSize())
           maxTreeSize = newParents.back().getTreeSize();
       //clock_t p2 = clock();
       //Logger::printInfo(" TimesSelectBestFromRandTwo: " + std::to_string(p2-p1));
    }
    //clock_t p2 = clock();
    std::swap(population, newParents);
    Logger::printInfo("MaxTreeSize in this selection is: " + std::to_string(maxTreeSize));
    //clock_t p3 = clock();
    //Logger::printInfo(" TimesSelect: push_back|copy: " + std::to_string(p2-p1)+"|" +std::to_string(p3-p2));
}

ExpressionTree GeneticAlgorithm::selectBestFromRandTwo(std::vector<ExpressionTree>& expTreesVec)
{
    unsigned rand1 = Helper::getRandomNumber()%expTreesVec.size();
    unsigned rand2 = Helper::getRandomNumber()%expTreesVec.size();

    return (evaluateTree(expTreesVec[rand1]) < evaluateTree(expTreesVec[rand2])) ? expTreesVec[rand1] : expTreesVec[rand2];
}

double GeneticAlgorithm::evaluateTree(ExpressionTree &expTree)
{
    double evalTree = 0;
    for(unsigned i = 0; i < dataValues.size(); ++i)
    {
        expTree.setVariablesValues(dataValues[i]);
        evalTree += pow(dataResults[i] - expTree.getResult(), 2);

        if(std::isnan(expTree.getResult()))
           throw std::exception();
    }
    return evalTree;
}

void GeneticAlgorithm::crossOver(const unsigned& crossOverProb, std::vector<ExpressionTree>& population)
{
    std::vector<ExpressionTree> childrensPopulation;
    childrensPopulation.reserve(population.size()*1.5);

    while(!population.empty())
    {
        std::pair<ExpressionTree, ExpressionTree> expTreePair = std::move(withdrawTreesPair(population));
        if(Helper::getRandomNumber()%101 < crossOverProb)
            crossOverTreesPair(expTreePair);
        childrensPopulation.push_back(expTreePair.first);
        childrensPopulation.push_back(expTreePair.second);
    }
    std::swap(population, childrensPopulation);
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
