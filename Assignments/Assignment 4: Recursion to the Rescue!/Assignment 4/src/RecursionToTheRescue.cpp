#include "RecursionToTheRescue.h"
#include "map.h"
#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define INT_MAX 1e9;

using namespace std;

/* * * * Doctors Without Orders * * * */

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */

bool checkSchedule(const Vector<Doctor>& doctors, const Vector<Patient>& patients,
                   vector<int>& ofPatient, bool& check) {

    vector<int> timeofDoctor(doctors.size(), 0);
    for (int i = 0; i < patients.size(); ++i) {
        int doctorId = ofPatient[i];
        timeofDoctor[doctorId] += patients[i].hoursNeeded;
        if (patients[i].hoursNeeded > doctors[doctorId].hoursFree)
            return false;
    }
    for (int i = 0; i < doctors.size(); ++i) {
        if (timeofDoctor[i] > doctors[i].hoursFree)
            return false;
    }
    return true;
}

void updateSchedule(const Vector<Doctor>& doctors, const Vector<Patient>& patients,
                    vector<int>& ofPatient, Map<string, Set<string>>& schedule) {
    for (int i = 0; i < patients.size(); ++i) {
        int doctorId = ofPatient[i];
        schedule[doctors[doctorId].name] += patients[i].name;
    }
}

void backTrackingPart1(const Vector<Doctor>& doctors, const Vector<Patient>& patients,
                  vector<int>& ofPatient, bool& check, int id,
                  Map<string, Set<string>>& schedule) {
    //**************************//
    if (check == true)
        return;
    for (int i = 0; i < doctors.size(); ++i) {
        ofPatient[id] = i;
        if (id == patients.size() - 1) {
            bool ans = checkSchedule(doctors, patients, ofPatient, check);
            if (ans == true) {
                check = true;
                updateSchedule(doctors, patients, ofPatient, schedule);
            }
        } else {
            backTrackingPart1(doctors, patients, ofPatient, check, id + 1, schedule);
        }
    }
}

bool canAllPatientsBeSeen(const Vector<Doctor>& doctors,
                          const Vector<Patient>& patients,
                          Map<string, Set<string>>& schedule) {
    // [TODO: Delete these lines and implement this function!]
    //(void)(doctors, patients, schedule);
    vector<int> ofPatient(patients.size(), 0);
    bool check = false;
    if (patients.isEmpty())
        return true;

    backTrackingPart1(doctors, patients, ofPatient, check, 0, schedule);

    //cout << check << endl;
    return check;
}

/* * * * Disaster Planning * * * */

/**
 * Given a transportation grid for a country or region, along with the number of cities where disaster
 * supplies can be stockpiled, returns whether it's possible to stockpile disaster supplies in at most
 * the specified number of cities such that each city either has supplies or is connected to a city that
 * does.
 * <p>
 * This function can assume that every city is a key in the transportation map and that roads are
 * bidirectional: if there's a road from City A to City B, then there's a road from City B back to
 * City A as well.
 *
 * @param roadNetwork The underlying transportation network.
 * @param numCities   How many cities you can afford to put supplies in.
 * @param locations   An outparameter filled in with which cities to choose if a solution exists.
 * @return Whether a solution exists.
 */

bool checkCoverAll(const Map<string, Set<string>>& roadNetwork, const Set<string>& exploredGraph) {
    if (exploredGraph.size() == roadNetwork.keys().size())
        return true;
    return false;
}

void poluteLocations (const vector<string>& choseCities, Set<string>& locations, const int& numCities, const bool& check){
    int i = 0;
    if (check)
        return;
    while (i <= numCities - 1 && choseCities[i] != "") {
        locations += choseCities[i];
        i += 1;
    }
    return;
}

void backTrackingPart2(const Map<string, Set<string>>& roadNetwork, int numCities, Set<string>& locations, bool& check,
                       vector<string>& choseCities, Map<string, bool>& isChose,
                       const Set<string> exploredGraph, const Set<string> remainingCities,
                       int turn) {

    if (check == true)
        return;

    string choseCity = *remainingCities.begin();
    Set<string> choseSet;
    choseSet += choseCity;
    choseSet += roadNetwork[choseCity];

    for (string city : choseSet) {
        if (!isChose[city]) {
            choseCities[turn] = city;

            isChose[city] = true;
            Set<string> nextExploredGraph = exploredGraph;
            nextExploredGraph += city;
            nextExploredGraph += roadNetwork[city];

            Set<string> nextRemainingCities = remainingCities;
            nextRemainingCities -= city;
            nextRemainingCities -= roadNetwork[city];


            bool ans = checkCoverAll(roadNetwork, nextExploredGraph);
            if (ans) {
                poluteLocations(choseCities, locations, numCities, check);
                check = true;
            } else if (turn < numCities - 1) {
                backTrackingPart2(roadNetwork, numCities, locations, check, choseCities, isChose, nextExploredGraph, nextRemainingCities, turn + 1);
            }

            isChose[city] = false;
            choseCities[turn] = "";
        }

    }
}

bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& locations) {
    // [TODO: Delete these lines and implement this function!]
    //(void)(roadNetwork, numCities, locations);

    int totalCities = roadNetwork.keys().size();
    if (numCities == 0 && totalCities > 0)
        return false;
    else if (numCities >= totalCities) {
        for (string city : roadNetwork.keys())
            locations += city;
        return true;
    }

    bool check = false;

    vector<string> choseCities(numCities, "");
    Map<string, bool> isChose;
    Set<string> exploredGraph;
    Set<string> remainingCities;

    for (string city : roadNetwork.keys()) {
        isChose[city] = false;
        remainingCities += city;
        remainingCities += roadNetwork[city];
    }

    backTrackingPart2(roadNetwork, numCities, locations, check, choseCities, isChose, exploredGraph, remainingCities, 0);

    return check;
}

/* * * * DNA Detective * * * */

/**
 * Given two DNA strands and a maximum edit distance, returns whether those two strands are
 * within that edit distance of one another.
 *
 * @param one The first DNA strand.
 * @param two The second DNA strand.
 * @param maxDistance The maximum distance between them.
 * @return Whether the two strands are within that edit distance of one another.
 */

int editDistance(const string& one, const string& two, int i, int j) {
    if (i == one.length() || j == two.length()) {
        return (one.length() - i + two.length() - j);
    } else if (one[i] == two[j]) {
        return editDistance(one, two, i + 1, j + 1);
    } else {
        int minDistance = min(editDistance(one, two, i + 1, j), editDistance(one, two, i, j + 1));
        minDistance = min(minDistance, editDistance(one, two, i + 1, j + 1));
        return 1 + minDistance;
    }
}

bool approximatelyMatch(const string& one, const string& two, int maxDistance) {
    // [TODO: Delete these lines and implement this function!]
    //(void)(one, two, maxDistance);
    //cout << editDistance(one, two, 0, 0) << endl;

    return editDistance(one, two, 0, 0) == maxDistance;

}

/* * * * Winning the Election * * * */

/**
 * Given a list of all the states in an election, including their popular and electoral vote
 * totals, returns information about how few popular votes you'd need to win in order to win
 * the presidency.
 *
 * @param states All the states in the election (plus DC, if appropriate)
 * @return Information about how few votes you'd need to win the election.
 */
MinInfo minPopularVoteToWin(const Vector<State>& states) {
    // [TODO: Delete these lines and implement this function!]
    //(void)(states);

    MinInfo ans = { 0, {} };
    Set<int> neededStates;

    int totalElectoralVotes = 0;
    int numStates = states.size();


    for (State state : states) {
        totalElectoralVotes += state.electoralVotes;
    }

    int neededElectoralVotes = (totalElectoralVotes + 2) / 2;

    int** f = new int*[neededElectoralVotes + 1];
    for (int i = 0; i <= neededElectoralVotes; ++i)
        f[i] = new int[numStates + 1];

    for (int i = 0; i <= neededElectoralVotes; ++i) {
        for (int j = 0; j <= numStates; ++j) {
            if (i == 0) {
                f[i][j] = 0;
                continue;
            } else if (j == 0) {
                f[i][j] = INT_MAX;
            } else if (i <= states[j - 1].electoralVotes) {
                int tmp = (states[j - 1].popularVotes + 2) / 2;
                f[i][j] = min(f[i][j - 1], tmp);
                if (f[i][j] == tmp)
                    neededStates.add(j - 1);
            } else {
                int tmp = f[i - states[j - 1].electoralVotes][j - 1] + (states[j - 1].popularVotes + 2) / 2;
                f[i][j] = min(f[i][j - 1], tmp);
                if (f[i][j] == tmp)
                    neededStates.add(j - 1);
            }
        }
    }
    ans.popularVotesNeeded = f[neededElectoralVotes][numStates];
    for (int id : neededStates)
        ans.statesUsed.push_back(states[id]);
    return ans;
}
