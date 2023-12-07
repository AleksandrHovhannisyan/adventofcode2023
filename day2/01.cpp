#include <cctype>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <utility>

struct Cube {
    std::regex pattern;
    int maxAllowedCount;
};

std::vector<Cube> CUBES = {
    { .pattern = std::regex {"(\\d+) red"}, .maxAllowedCount = 12},
    { .pattern = std::regex {"(\\d+) green"}, .maxAllowedCount = 13},
    { .pattern = std::regex {"(\\d+) blue"}, .maxAllowedCount = 14},
};

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

bool isGamePossible(std::string game) {
    bool isPossible = true;
    for (auto cube : CUBES) {
        auto cubeCounts = getCubeCounts(game, cube.pattern);
        for (auto count : cubeCounts) {
            if (count > cube.maxAllowedCount) {
                isPossible = false;
                break;
            }
        }
    }
    return isPossible;
};

std::vector<std::string> getLinesOfText(std::ifstream& inputFile) {
    std::vector<std::string> lines { };
    std::string line { "" };
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    return lines;
};

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    std::vector<std::string> lines = getLinesOfText(inputFile);

    int sumOfPossibleGameIds = 0;
    int gameId = 1;

    for (const auto& game : lines) {
        if (isGamePossible(game)) {
            sumOfPossibleGameIds += gameId;
        }
        gameId++;
    }

    std::cout << "Answer: " << sumOfPossibleGameIds << std::endl;
    inputFile.close();
    return 0;
}
