#ifndef ABSTRACT_ALGORITHM_H
#define ABSTRACT_ALGORITHM_H

#include "Resources.h"

class AbstractAlgorithm {
public:
    virtual ~AbstractAlgorithm() = default;

    virtual void calculateFairTeams(res::playerStatistics&& statistics) = 0;
    virtual void printCalculatedTeams() = 0;

    virtual double getRatingOfTeamA() const = 0;
    virtual double getRatingOfTeamB() const = 0;
};

#endif // ABSTRACT_ALGORITHM_H
