#include <algorithm>
#include <cctype>
#include <numeric>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <utility>

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

std::vector<std::string> getLinesOfText(std::ifstream& inputFile) {
    std::vector<std::string> lines { };
    std::string line { "" };
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }
    return lines;
};

int getPower(std::string game) {
    auto redCubes = getCubeCounts(game, std::regex { "(\\d+) red" });
    auto greenCubes = getCubeCounts(game, std::regex { "(\\d+) green" });
    auto blueCubes = getCubeCounts(game, std::regex { "(\\d+) blue" });
    
    auto minRedCubes = *std::max_element(redCubes.begin(), redCubes.end());
    auto minGreenCubes = *std::max_element(greenCubes.begin(), greenCubes.end());
    auto minBlueCubes = *std::max_element(blueCubes.begin(), blueCubes.end());
    return minRedCubes * minGreenCubes * minBlueCubes;
};

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");
    std::vector<std::string> lines = getLinesOfText(inputFile);
    int powerSum = 0;
    for (const auto& game : lines) {
        powerSum += getPower(game);
    }
    std::cout << "Answer: " << powerSum << std::endl;
    inputFile.close();
    return 0;
}
