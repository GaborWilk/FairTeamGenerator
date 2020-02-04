#ifndef RESOURCES_H
#define RESOURCES_H

#include <iosfwd>
#include <sstream>

#include <string>
#include <vector>


namespace res {

    // Alias to store statistical data about players
    using playerData = std::pair<std::string, unsigned int>;
    using playerStatistics = std::vector<playerData>;

    // Number of players: 4
    constexpr unsigned short NUM_OF_PLAYERS_FOUR = 4;

    // Number of players: 6
    constexpr unsigned short NUM_OF_PLAYERS_SIX = 6;

    // Number of players: 8
    constexpr unsigned short NUM_OF_PLAYERS_EIGHT = 8;

    // The required minimum value of player's rating
    constexpr unsigned int RATING_VALUE_MIN = 1;

    // The maximum allowed value of players' rating
    constexpr unsigned int RATING_VALUE_MAX = 5000;

    // Additional namespace for overriding ostream << operator (for convenience)
    // This solution is better, than using static_cast or "+" sign before "unsigned char" and "signed char" variables, because
    // "unsigned char" and "signed char" are basically types of char, thus cout prints characters instead of integer values.
    namespace bytes {
        inline std::ostream& operator<<(std::ostream& os, const char c) {
            return os << (std::is_signed<char>::value ? static_cast<int>(c) : static_cast<unsigned int>(c));
        }

        inline std::ostream& operator<<(std::ostream& os, const signed char c) {
            return os << static_cast<int>(c);
        }

        inline std::ostream& operator<<(std::ostream& os, const unsigned char c) {
            return os << static_cast<unsigned int>(c);
        }
    } // namespace bytes

} // namespace res

#endif // RESOURCES_H
