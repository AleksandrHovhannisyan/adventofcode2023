#include <algorithm>
#include <cctype>
#include <numeric>
#include <sstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include "../utils.h"

std::regex REGEX_RED { "(\\d+) red" };
std::regex REGEX_GREEN { "(\\d+) green" };
std::regex REGEX_BLUE { "(\\d+) blue" };

std::vector<int> getCubeCounts(std::string game, std::regex pattern) {
    std::vector<int> cubeCounts;
    // When using regex, we don't even have to split the input string by the semicolons for rounds; we can just repeatedly match
    std::sregex_iterator regexIterator { game.begin(), game.end(), pattern };
    std::sregex_iterator regexEnd;

    while (regexIterator != regexEnd) {
        auto matches = *regexIterator;
        if (matches.size()) {
            int numCubes = std::stoi(matches[matches.size() - 1].str());
            cubeCounts.push_back(numCubes);
        }
        regexIterator++;
    }

    return cubeCounts;
};

int getPower(std::string game) {
    auto redCubes = getCubeCounts(game, REGEX_RED);
    auto greenCubes = getCubeCounts(game, REGEX_GREEN);
    auto blueCubes = getCubeCounts(game, REGEX_BLUE);
    
    auto minRedCubes = *std::max_element(redCubes.begin(), redCubes.end());
    auto minGreenCubes = *std::max_element(greenCubes.begin(), greenCubes.end());
    auto minBlueCubes = *std::max_element(blueCubes.begin(), blueCubes.end());
    return minRedCubes * minGreenCubes * minBlueCubes;
};

int main() {
    std::vector<std::string> games = getInputLines("./input.txt");
    int sum = std::accumulate(games.begin(), games.end(), 0, [](int sum, const std::string& game) { return sum + getPower(game);});
    std::cout << "Answer: " << sum << std::endl;
    return 0;
}
