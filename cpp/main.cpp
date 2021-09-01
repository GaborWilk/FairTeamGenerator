#include "include/AbstractAlgorithm.h"
#include "include/GreedyAlgorithm.h"
#include "include/FairTeamGenerator.h"
#include "include/Resources.h"

#include <iostream>
#include <memory>

using namespace ftg;


int main() {
    unsigned short numOfPlayers = 0;
    auto& FTG = FairTeamGenerator::getInstance();

    while (true) {
        std::cout << "_________________________________" << std::endl;
        std::cout << "Enter the number of players: ";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);

        if ((!(ss >> numOfPlayers)) ||
           ((NUM_OF_PLAYERS_FOUR != numOfPlayers) && (NUM_OF_PLAYERS_SIX != numOfPlayers) && (NUM_OF_PLAYERS_EIGHT != numOfPlayers))) {
            std::cout << std::endl << "Enter a valid number of players (4, 6 or 8)!" << std::endl;
            continue;
        }

        break;
    }

    FTG.setNumOfPlayers(numOfPlayers);

    for (auto i = 0; i < numOfPlayers; ++i) {
        std::cout << "Name of Player" << i + 1 << " : ";
        unsigned int rating = 0;
        std::string nickName;

        std::getline(std::cin, nickName);
        std::stringstream ss(nickName);

        while (true) {
            std::cout << "Rating of Player" << i + 1 << " : ";
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            if ((!(ss >> rating)) || ((rating < RATING_VALUE_MIN) || (rating > RATING_VALUE_MAX))) {
                std::cout << std::endl << "Enter a valid rating between [" << RATING_VALUE_MIN << "..." << RATING_VALUE_MAX << "]!" << std::endl;
                continue;
            }

            break;
        }

        FTG.setPlayerRating(nickName, rating);
    }

    std::cout << "Calculating fair teams for " << numOfPlayers << " players...";

    auto alg = std::make_unique<GreedyAlgorithm>();
    FTG.setAlgorithmType(std::move(alg));
    FTG.useAlgorithm();

    return 0;
}

