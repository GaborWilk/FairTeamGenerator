#include "Resources.h"
#include "GreedyAlgorithm.h"
#include "PrintTeams.h"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

// using Resources features
using namespace res;


void GreedyAlgorithm::calculateFairTeams(playerStatistics&& player)
{
    // sort players by DSC
    std::sort(player.begin(), player.end(), [](const auto& lhs, const auto& rhs)
    {
        return lhs.second > rhs.second;
    });

    // best player will be in teamA, 2nd in teamB, lowest overall team choose next
    avgOfTeamA_ += player[0].second;
    playersOfTeamA_.emplace_back(player[0]);
    avgOfTeamB_ += player[1].second;
    playersOfTeamB_.emplace_back(player[1]);

    for(unsigned i = 2; i < player.size(); ++i) {
        if(avgOfTeamA_ < avgOfTeamB_) {
            avgOfTeamA_ += player[i].second;
            playersOfTeamA_.emplace_back(player[i]);
        } else {
            avgOfTeamB_ += player[i].second;
            playersOfTeamB_.emplace_back(player[i]);
        }
    }

    avgOfTeamA_ /= (player.size() / 2);
    avgOfTeamB_ /= (player.size() / 2);

    printCalculatedTeams();
}

void GreedyAlgorithm::printCalculatedTeams()
{
    printTeam_.printTeams(std::move(playersOfTeamA_), getRatingOfTeamA(), std::move(playersOfTeamB_), getRatingOfTeamB());
}

double GreedyAlgorithm::getRatingOfTeamA() const
{
    return avgOfTeamA_;
}

double GreedyAlgorithm::getRatingOfTeamB() const
{
    return avgOfTeamB_;
}

