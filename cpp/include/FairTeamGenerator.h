#ifndef FAIR_TEAM_GENERATOR_H
#define FAIR_TEAM_GENERATOR_H

#include <include/AbstractAlgorithm.h>
#include <include/Resources.h>

#include <memory>

// using FairTeamGenerator features
namespace ftg {

    // using Resources features
    using namespace res;

    // Alias to store algorithm type
    using algorithmType = std::unique_ptr<AbstractAlgorithm>;

    // FairTeamGenerator class to store players' data and generate two fair teams based on statistics (e.g. rating)
    class FairTeamGenerator {
      public:
        // get FairTeamGenerator class instance by using Singleton design pattern with lazy initialization (thread-safe)
        static FairTeamGenerator& getInstance() {
            static FairTeamGenerator instance;
            return instance;
        }

        FairTeamGenerator(const FairTeamGenerator&) = delete;
        FairTeamGenerator& operator= (const FairTeamGenerator&) = delete;
        FairTeamGenerator& operator= (FairTeamGenerator&&) = delete;
        FairTeamGenerator(FairTeamGenerator&&) = delete;

        void setNumOfPlayers(unsigned short num);
        unsigned short getNumOfPlayers() const;

        void setPlayerRating(const std::string& name, unsigned int rating);
        auto getPlayerRatingByName(const std::string& name) const;

        double getAverageRatingOfTeamA() const;
        double getAverageRatingOfTeamB() const;

        void useAlgorithm();
        void setAlgorithmType(std::unique_ptr<AbstractAlgorithm> ptr);

      private:
        explicit FairTeamGenerator() {}
        ~FairTeamGenerator() = default;

        algorithmType algorithm_;
        unsigned short numOfPlayers_ = 0;
        playerStatistics players_;
    };

} // namespace ftg

#endif // FAIR_TEAM_GENERATOR_H
