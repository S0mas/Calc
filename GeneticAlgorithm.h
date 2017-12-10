#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include "RandomTreeGenerator.h"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm();

    void process(const unsigned& populationSize, const unsigned& iterationNumber, const unsigned& crossOverProb, const unsigned& mutateProb);

private:
    void loadDataFile();
    bool checkData();
    void initiate(const unsigned& populationSize, std::vector<ExpressionTree>& population);
    void select(const unsigned& populationSize, std::vector<ExpressionTree>& population);
    ExpressionTree selectBestFromRandTwo(std::vector<ExpressionTree> &expTreesVec);
    unsigned evaluateTree(ExpressionTree &expTree);
    void crossOver(const unsigned& crossOverProb, std::vector<ExpressionTree> &expTreesVec);
    void crossOverTreesPair(std::pair<ExpressionTree, ExpressionTree> &expTreesPair);
    std::pair<ExpressionTree, ExpressionTree> withdrawTreesPair(std::vector<ExpressionTree> &expTreesVec);
    ExpressionTree withdrawRandTree(std::vector<ExpressionTree> &expTreesVec);
    void mutate(const unsigned& mutateProb, std::vector<ExpressionTree> &expTreesVec);

    RandomTreeGenerator randTreeGen;
    std::vector<std::vector<double>> data;

};

#endif // GENETICALGORITHM_H
