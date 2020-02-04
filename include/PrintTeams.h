#ifndef PRINT_TEAMS_H
#define PRINT_TEAMS_H

#include <include/Resources.h>

class PrintTeams {
  public:
    void printTeams(res::playerStatistics&& teamA, double avgOfTeamA, res::playerStatistics&& teamB, double avgOfTeamB) const;

  private:
    void printPlayers(res::playerStatistics&& player) const;
};

#endif // PRINT_TEAMS_H
