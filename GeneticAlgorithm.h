#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "RandomTreeGenerator.h"

struct Setup
{
    Setup(unsigned pop, unsigned it, unsigned cross, unsigned mutate, int id)
        : population(pop), iteration(it), crossChance(cross), mutationChance(mutate), id(id){}
    unsigned population;
    unsigned iteration;
    unsigned crossChance;
    unsigned mutationChance;
    int id;
};

class GeneticAlgorithm
{
public:
    struct Result
    {
        std::string expression;
        long double value;
    };

    GeneticAlgorithm();

    Result process(const Setup& setup);

private:
    void loadDataFile();
    bool checkData();
    void initiate(const unsigned& populationSize, std::vector<ExpressionTree>& population);
    void select(const unsigned& populationSize, std::vector<ExpressionTree>& population);
    ExpressionTree selectBestFromRandTwo(std::vector<ExpressionTree> &expTreesVec);
    long double evaluateTree(ExpressionTree &expTree);
    void crossOver(const unsigned& crossOverProb, std::vector<ExpressionTree> &expTreesVec);
    void crossOverTreesPair(std::pair<ExpressionTree, ExpressionTree> &expTreesPair);
    std::pair<ExpressionTree, ExpressionTree> withdrawTreesPair(std::vector<ExpressionTree> &expTreesVec);
    ExpressionTree withdrawRandTree(std::vector<ExpressionTree> &expTreesVec);
    void mutate(const unsigned& mutateProb, std::vector<ExpressionTree> &expTreesVec);

    std::vector<std::vector<double>> data;



};

#endif // GENETICALGORITHM_H
