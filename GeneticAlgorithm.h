#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "RandomTreeGenerator.h"
#include "limits"

struct Setup
{
    Setup(unsigned pop, unsigned it, unsigned cross, unsigned mutate, int id)
        : population(pop), iteration(it), crossChance(cross), mutationChance(mutate), id(id){}
    unsigned population;
    unsigned iteration;
    unsigned crossChance;
    unsigned mutationChance;
    int id;

    std::string toString()
    {
        return "population:" + std::to_string(population) + " iteration:" + std::to_string(iteration)
                + " crossChance:" + std::to_string(crossChance) + " mutationChance:" + std::to_string(mutationChance);
    }
};

class GeneticAlgorithm
{
public:
    struct Result
    {
        Result() : expression(""), value(std::numeric_limits<double>::max()), choosenOne(false) {}

        std::string expression;
        double value;
        bool choosenOne;
    };

    GeneticAlgorithm();

    Result process(const Setup& setup);

private:
    void loadDataFile();
    bool checkData();
    void initiate(const unsigned& populationSize, std::vector<ExpressionTree>& population);
    void select(const unsigned& populationSize, std::vector<ExpressionTree>& population);
    ExpressionTree selectBestFromRandTwo(std::vector<ExpressionTree> &expTreesVec);
    double evaluateTree(ExpressionTree &expTree);
    void crossOver(const unsigned& crossOverProb, std::vector<ExpressionTree> &expTreesVec);
    void crossOverTreesPair(std::pair<ExpressionTree, ExpressionTree> &expTreesPair);
    std::pair<ExpressionTree, ExpressionTree> withdrawTreesPair(std::vector<ExpressionTree> &expTreesVec);
    ExpressionTree withdrawRandTree(std::vector<ExpressionTree> &expTreesVec);
    void mutate(const unsigned& mutateProb, std::vector<ExpressionTree> &expTreesVec);
    bool lookForGoldenChild(std::vector<ExpressionTree>& population, Result &result);

    std::vector<std::vector<double>> dataValues;
    std::vector<double> dataResults;
};

#endif // GENETICALGORITHM_H
