#include "utils.h"
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> getInputLines(std::string inputFilePath) {
	std::ifstream inputFile;
	inputFile.open(inputFilePath);

    std::vector<std::string> lines { };
    std::string line { "" };

    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();
    return lines;
};
