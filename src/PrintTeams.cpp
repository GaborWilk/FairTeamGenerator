#include <include/Resources.h>
#include <include/PrintTeams.h>

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace res;


void PrintTeams::printTeams(res::playerStatistics&& teamA, double avgOfTeamA,
                            res::playerStatistics&& teamB, double avgOfTeamB) const {
    std::cout << std::endl << std::endl << "********************************************" << std::endl;

    std::cout << "===============[ TEAM A ]====================" << std::endl;
    printPlayers(std::move(teamA));
    std::cout << std::endl << "Team average: " << avgOfTeamA << std::endl;

    std::cout << "===============[ TEAM B ]====================" << std::endl;
    printPlayers(std::move(teamB));
    std::cout << std::endl << "Team average: " << avgOfTeamB << std::endl;

    std::cout << "____________________________________________" << std::endl;
    std::cout.precision(2);
    std::cout << "Difference between the teams: " << std::fixed << std::fabs(avgOfTeamA - avgOfTeamB) << std::endl;
    std::cout << "********************************************" << std::endl;
}

void PrintTeams::printPlayers(res::playerStatistics&& player) const {
    for (auto& it : player) {
        std::cout << "Nickname: " << it.first << " (Rating: " << it.second << ")" << std::endl;
    }
}
