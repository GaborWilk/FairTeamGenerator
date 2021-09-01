from operator import itemgetter
from multiprocessing.pool import Pool
from multiprocessing import cpu_count
import time
from functools import partial
from abc import ABC, abstractmethod
from itertools import repeat


class Algorithm(ABC):
    """
    The Algorithm interface declares operations common to all supported versions
    of some algorithm.

    The FairTeamGenerator uses this interface to call the algorithm defined by concrete
    algorithm classes.
    """
    @abstractmethod
    def calculate_teams(self, players_):
        pass


class Greedy(Algorithm):
    """
    The Greedy algorithm sorts players into two teams to get the minimal total difference
    in team average rating values. The algorithm starts with separating the the best players,
    after that the weaker team chooses the next player until there are no more players.
    """
    def calculate_teams(self, players_):
        start_time = time.time()
        start_time_ns = time.time_ns()
        team_first = [players_[0]]
        team_second = [players_[1]]

        team_first_sum = team_first[0][1]
        team_second_sum = team_second[0][1]

        for player in players_[2:]:
            if team_first_sum < team_second_sum:
                team_first.append(player)
                team_first_sum += player[1]
            else:
                team_second.append(player)
                team_second_sum += player[1]
        print(f"[*] Greedy finished in: {time.time() - start_time}s (or {time.time_ns() - start_time_ns}ns)")

        return team_first, team_second, team_first_sum / len(team_first), team_second_sum / len(team_second)


class Neighbourhood(Algorithm):
    """
    The Neighbourhood algorithm sorts players into two teams to get the minimal total difference
    in team average rating values. The algorithm starts with separating the the best players,
    after that the teams choose the next players alternately until there are no more players.
    """
    def calculate_teams(self, players_):
        start_time = time.time()
        start_time_ns = time.time_ns()
        team_first = [players_[0]]
        team_second = [players_[1]]

        team_first_sum = team_first[0][1]
        team_second_sum = team_second[0][1]

        for idx, player in enumerate(players_[2:]):
            if 0 == idx % 2:
                team_first.append(player)
                team_first_sum += player[1]
            else:
                team_second.append(player)
                team_second_sum += player[1]
        print(f"[*] Neighbour finished in: {time.time() - start_time}s (or {time.time_ns() - start_time_ns}ns)")

        return team_first, team_second, team_first_sum / len(team_first), team_second_sum / len(team_second)


class NegativeNeighbourhood(Algorithm):
    """
    The NegativeNeighbourhood algorithm sorts players into two teams to get the minimal total difference
    in team average rating values. The algorithm starts with separating the two weakest players,
    after that the teams choose the next players alternately until there are no more players.
    """
    def calculate_teams(self, players_):
        start_time = time.time()
        start_time_ns = time.time_ns()
        last_index = len(players_) - 1
        team_first = [players_[last_index]]
        team_second = [players_[last_index - 1]]

        team_first_sum = team_first[0][1]
        team_second_sum = team_second[0][1]

        for idx, player in reversed(list(enumerate(players_[:-2]))):
            if 0 == idx % 2:
                team_first.append(player)
                team_first_sum += player[1]
            else:
                team_second.append(player)
                team_second_sum += player[1]
        print(f"[*] Neighbour finished in: {time.time() - start_time}s (or {time.time_ns() - start_time_ns}ns)")

        return team_first, team_second, team_first_sum / len(team_first), team_second_sum / len(team_second)


class Players:
    """
    Storage class for players with nicknames and rating values.
    """
    __slots__ = ["_players"]

    def __init__(self):
        self._players = []

    def add_player(self, nickname_, rating_):
        if [player for player in self._players if nickname_ in player]:
            raise ValueError
        else:
            self._players.append((nickname_, rating_))

    def get_players(self):
        return self._players

    def sort_players(self):
        self._players.sort(key=itemgetter(1), reverse=True)


class FairTeamGenerator:
    """
    The FairTeamGenerator is responsible to generate fair teams based on the
    players rating values, so the total difference between the teams is minimal.
    """
    __slots__ = ["_players", "_algorithms", "_pool_functions", "_result"]

    def __init__(self):
        self._players = []
        self._algorithms = []
        self._pool_functions = []
        self._result = []

    @staticmethod
    def parallelize(workers_num, functions, arguments):
        # if we need this multiple times, instantiate the pool outside and
        # pass it in as dependency to spare recreation all over again
        with Pool(workers_num) as pool:
            tasks = zip(functions, repeat(arguments))
            futures = [pool.apply_async(*t) for t in tasks]
            results = [fut.get() for fut in futures]
        return results

    def add_players(self, players_):
        self._players = players_

    def set_algorithm(self, *algorithms):
        for alg in algorithms:
            self._algorithms.append(alg)

    def calculate_teams(self):
        for alg in self._algorithms:
            self._pool_functions.append((partial(alg.calculate_teams, self._players)))

        start_time_algs = time.time()
        start_time_algs_ns = time.time_ns()

        # call algorithms parallel
        functions = self._algorithms[0].calculate_teams, \
                    self._algorithms[1].calculate_teams, \
                    self._algorithms[2].calculate_teams
        self._result = self.parallelize(NUM_OF_WORKERS, functions, arguments=(self._players,))

        end_time_algs = time.time()
        end_time_algs_ns = time.time_ns()
        print("#-------------------------------#")
        print(f"Overall time taken: {end_time_algs - start_time_algs}s (or {end_time_algs_ns - start_time_algs_ns}ns)")

    def print_teams(self):
        print("#-------------------------------#")
        print("#---------- GREEDY -------------#")
        print("#-------------------------------#")
        print("First team:")
        for player in self._result[0][0]:
            print(player[0] + " - " + str(player[1]))
        print("Team average:")
        print(self._result[0][2])
        print("#-------------------------------#")
        print("Second team:")
        for player in self._result[0][1]:
            print(player[0] + " - " + str(player[1]))
        print("Team average:")
        print(self._result[0][3])

        print("#-------------------------------#")
        print("#------------- NGH -------------#")
        print("#-------------------------------#")
        print("First team:")
        for player in self._result[1][0]:
            print(player[0] + " - " + str(player[1]))
        print("Team average:")
        print(self._result[1][2])
        print("#-------------------------------#")
        print("Second team:")
        for player in self._result[1][1]:
            print(player[0] + " - " + str(player[1]))
        print("Team average:")
        print(self._result[1][3])

        print("#-------------------------------#")
        print("#------------ NNGH -------------#")
        print("#-------------------------------#")
        print("First team:")
        for player in self._result[2][0]:
            print(player[0] + " - " + str(player[1]))
        print("Team average:")
        print(self._result[2][2])
        print("#-------------------------------#")
        print("Second team:")
        for player in self._result[2][1]:
            print(player[0] + " - " + str(player[1]))
        print("Team average:")
        print(self._result[2][3])

        # get differences between teams
        diff_grd = abs(self._result[0][2] - self._result[0][3])
        diff_ngh = abs(self._result[1][2] - self._result[1][3])
        diff_nngh = abs(self._result[2][2] - self._result[2][3])

        # store differences with algorithm names
        total_differences = {
            "Greedy": diff_grd,
            "Neighbour": diff_ngh,
            "Negative Neighbour": diff_nngh
        }
        total_differences = {k: v for k, v in sorted(total_differences.items(), key=lambda item: item[1])}

        # chose best algorithm
        best_choice = list(total_differences.items())[0]
        print("#-------------------------------#")
        print("Best algorithm: {} with team rating difference of {:.2f}".format(best_choice[0], best_choice[1]))


def read_nickname(index):
    nickname_ = input(f"Give the nickname of player {index + 1}: ")
    return nickname_


def read_rating(nickname_):
    rating_ = int(input(f"Give the rating of {nickname_}: "))
    return rating_


# Press the green button in the gutter to run the script.
if __name__ == '__main__':

    NUM_OF_PLAYERS_4 = 4
    NUM_OF_PLAYERS_6 = 6
    NUM_OF_PLAYERS_8 = 8

    # limit maximal number of worker processes to CPU limit
    NUM_OF_WORKERS = max(cpu_count() - 1, 1)

    # get number of players
    num_of_players = 0
    print("Currently only 4, 6 or 8 players are allowed to use.\n")
    while True:
        try:
            num_of_players = int(input("Enter the number of players: "))
            if NUM_OF_PLAYERS_4 != num_of_players and \
               NUM_OF_PLAYERS_6 != num_of_players and \
               NUM_OF_PLAYERS_8 != num_of_players:
                print("Invalid number of players, it should be 4, 6 or 8. Try again.")
                continue
        except ValueError:
            print("Invalid type of number of players, it should be an integer value of 4, 6 or 8. Try again.")
            continue
        else:
            break

    ftg = FairTeamGenerator()
    algorithm_greedy = Greedy()
    algorithm_nbh = Neighbourhood()
    algorithm_nnbh = NegativeNeighbourhood()
    ftg.set_algorithm(algorithm_greedy, algorithm_nbh, algorithm_nnbh)

    players = Players()
    for i in range(num_of_players):
        while True:
            nickname = ""
            rating = 0

            # read nickname first
            while True:
                nickname = read_nickname(i)
                if len(nickname) < 3:
                    print("Too short nickname, it should be at least 3 characters long. Try again.")
                    continue
                break

            # read corresponding rating
            while True:
                try:
                    rating = read_rating(nickname)
                    if rating < 100 or rating > 5000:
                        print("Invalid range for rating, it should be between 100 and 5000. Try again.")
                        continue
                except ValueError:
                    print("Invalid rating format: only integers are allowed. Try again.")
                    continue
                else:
                    break

            # store player's nickname and rating
            try:
                players.add_player(nickname, rating)
            except ValueError:
                print(f"The nickname of {nickname} is already entered. Use another.")
                continue
            else:
                break

    print("You entered the following:")
    for player in players.get_players():
        print(player[0] + " - " + str(player[1]))

    # calculate fair teams
    print("#-------------------------------#")
    print("Now calculating fair teams...")

    # sort player - rating pairs by descending order based on rating
    players.sort_players()

    # store players for internal use
    ftg.add_players(players.get_players())

    # calculate fair teams
    ftg.calculate_teams()

    # print teams
    ftg.print_teams()
