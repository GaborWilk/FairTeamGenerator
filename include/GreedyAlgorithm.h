#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H

#include "AbstractAlgorithm.h"
#include "Resources.h"
#include "PrintTeams.h"

class GreedyAlgorithm : public AbstractAlgorithm {
public:
    GreedyAlgorithm() = default;
    ~GreedyAlgorithm() override final {}

    void calculateFairTeams(res::playerStatistics&& player) override final;
    void printPlayers(res::playerStatistics&& player) const;
    void printCalculatedTeams() override final;

    double getRatingOfTeamA() const override final;
    double getRatingOfTeamB() const override final;

private:
    res::playerStatistics playersOfTeamA_;
    res::playerStatistics playersOfTeamB_;
    double avgOfTeamA_ = 0.0;
    double avgOfTeamB_ = 0.0;
    PrintTeams printTeam_;
};

#endif // GREEDY_ALGORITHM_H
