#include "GeneticAlgorithm.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <cmath>
#include <exception>
#include <QDir>

GeneticAlgorithm::Result GeneticAlgorithm::process(const Setup& setup, Data &data)
{
    dataValues = data.dataValues;
    dataResults = data.dataResults;
    Result result;
    bool foundChoosenOne = false;
    std::vector<ExpressionTree> population;
    population.reserve(setup.population*2);
    initiate(setup.population, population);
    if(!population.empty())
    {
        for(unsigned i = 0; i < setup.iteration; ++i)
        {
            foundChoosenOne = lookForGoldenChild(population, result);
            if(foundChoosenOne)
                break;
            select(setup.population, population);
            crossOver(setup.crossChance, population);
            mutate(setup.mutationChance, population);
        }
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
            }

            result.expression = population[bestId].toString();
            result.value = bestResult;
        }
    }
    else
        Logger::printError("Population is empty!");

    return result;
}

bool GeneticAlgorithm::lookForGoldenChild(std::vector<ExpressionTree>& population, Result& result) const
{
    bool found = false;
    for(auto& tree : population)
    {
        double temp = evaluateTree(tree);
        if( temp < 0.000001)
        {
            Logger::printInfo("Found ChoosenOne!");
            result.value = temp;
            result.expression = tree.toString();
            result.choosenOne = true;
            found = true;
            break;
        }
    }
    return found;
}


void GeneticAlgorithm::initiate(const unsigned &populationSize, std::vector<ExpressionTree>& population) const
{
    unsigned varsNumb = 2;
    unsigned minNodesNumber = 1;
    unsigned maxNodesNumber = 3;
    population.reserve(populationSize*2);

    for(unsigned i = 0; i < populationSize; ++i)
        population.push_back(RandomTreeGenerator::generateRandomTree(varsNumb, minNodesNumber, maxNodesNumber));
}

void GeneticAlgorithm::select(const unsigned& populationSize, std::vector<ExpressionTree>& population) const
{
    std::vector<ExpressionTree> newParents;
    newParents.reserve(populationSize*2);

    for(unsigned i = 0; i < populationSize; ++i)
        newParents.push_back(selectBestFromRandTwo(population));

    std::swap(population, newParents);
}

ExpressionTree GeneticAlgorithm::selectBestFromRandTwo(std::vector<ExpressionTree>& expTreesVec) const
{
    unsigned rand1 = Helper::getRandomNumber()%expTreesVec.size();
    unsigned rand2 = Helper::getRandomNumber()%expTreesVec.size();

    return ( evaluateTree(expTreesVec[rand1]) < evaluateTree(expTreesVec[rand2])) ? expTreesVec[rand1] : expTreesVec[rand2];
}

double GeneticAlgorithm::evaluateTree(ExpressionTree &expTree) const
{
    double evalTree = 0;

    for(unsigned i = 0; i < dataValues.size(); ++i)
    {
        expTree.setVariablesValues(dataValues[i]);
        double result = expTree.getResult();
        evalTree += pow(dataResults[i] - result, 2);

        if(std::isnan(result))
           throw std::exception();
    }
    return evalTree;
}

void GeneticAlgorithm::crossOver(const unsigned& crossOverProb, std::vector<ExpressionTree>& population) const
{
    std::vector<ExpressionTree> childrensPopulation;
    childrensPopulation.reserve(population.size()*2);

    while(!population.empty())
    {
        std::pair<ExpressionTree, ExpressionTree> expTreePair = withdrawTreesPair(population);
        if(Helper::getRandomNumber()%101 < crossOverProb)
            crossOverTreesPair(expTreePair);
        childrensPopulation.push_back(std::move(expTreePair.first));
        childrensPopulation.push_back(std::move(expTreePair.second));
    }
    std::swap(population, childrensPopulation);
}

void GeneticAlgorithm::crossOverTreesPair(std::pair<ExpressionTree, ExpressionTree> &expTreesPair) const
{
    ExpressionTree::crossOver(std::get<0>(expTreesPair), std::get<1>(expTreesPair));
}

std::pair<ExpressionTree, ExpressionTree> GeneticAlgorithm::withdrawTreesPair(std::vector<ExpressionTree> &expTreesVec) const
{
    return std::make_pair(withdrawRandTree(expTreesVec), withdrawRandTree(expTreesVec));
}

ExpressionTree GeneticAlgorithm::withdrawRandTree(std::vector<ExpressionTree> &expTreesVec) const
{
    unsigned rand = Helper::getRandomNumber()%expTreesVec.size();
    ExpressionTree randTree = std::move(expTreesVec[rand]);
    expTreesVec.erase(expTreesVec.begin()+rand);

    return randTree;
}

void GeneticAlgorithm::mutate(const unsigned& mutateProb, std::vector<ExpressionTree>& expTreesVec) const
{
    for(unsigned i = 0; i < expTreesVec.size(); ++i)
    {
        if(Helper::getRandomNumber()%101 < mutateProb)
            expTreesVec[i].mutate();
    }
}
