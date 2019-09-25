#include "FairTeamGenerator.h"
#include "Resources.h"
#include "GreedyAlgorithm.h"

#include <iostream>


namespace ftg {

    using namespace res;

    void FairTeamGenerator::setNumOfPlayers(unsigned short num) {
        numOfPlayers_ = num;
    }

    unsigned short FairTeamGenerator::getNumOfPlayers() const {
        return numOfPlayers_;
    }

    void FairTeamGenerator::setPlayerRating(const std::string& name, unsigned int rating) {
        players_.emplace_back(std::make_pair(name, rating));
    }

    auto FairTeamGenerator::getPlayerRatingByName(const std::string& name) const {
        unsigned int rating = 0;

        for (auto& it : players_) {
            if (name == it.first) {
                rating = it.second;
                break;
            }
        }

        return rating;
    }

    double FairTeamGenerator::getAverageRatingOfTeamA() const {
        return algorithm_->getRatingOfTeamA();
    }

    double FairTeamGenerator::getAverageRatingOfTeamB() const {
        return algorithm_->getRatingOfTeamB();
    }

    void FairTeamGenerator::setAlgorithmType(std::unique_ptr<AbstractAlgorithm> ptr) {
        algorithm_ = std::move(ptr);
    }

    void FairTeamGenerator::useAlgorithm() {
        algorithm_->calculateFairTeams(std::move(players_));
    }

} // namespace ftg
