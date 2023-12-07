#include <cctype>
#include <iostream>
#include <numeric>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>
#include "../utils.h"

#define SYMBOL_EMPTY '.'

// For convenience/readability. Could've also used std::pair
struct Cell {
    size_t rowIndex;
    size_t columnIndex;
};

bool hasNeighboringSymbol(const std::vector<std::string>& input, size_t rowIndex, size_t columnIndex) {
    size_t numRows = input.size();
    size_t numColumns = input[0].length();

    // For convenience, define all possible neighbor coordinates relative to current location in the input grid. We'll clamp/validate them once we loop over them. Borrowed this strat from my Conway's Game of Life implementation (Lua): https://github.com/AleksandrHovhannisyan/conways-game-of-life/
    std::vector<Cell> neighbors = {
        {.rowIndex = rowIndex - 1, .columnIndex = columnIndex},     // top
        {.rowIndex = rowIndex - 1, .columnIndex = columnIndex + 1}, // topRight
        {.rowIndex = rowIndex,     .columnIndex = columnIndex + 1}, // right
        {.rowIndex = rowIndex + 1, .columnIndex = columnIndex + 1}, // bottomRight
        {.rowIndex = rowIndex + 1, .columnIndex = columnIndex},     // bottom
        {.rowIndex = rowIndex + 1, .columnIndex = columnIndex - 1}, // bottomLeft
        {.rowIndex = rowIndex,     .columnIndex = columnIndex - 1}, // left
        {.rowIndex = rowIndex - 1, .columnIndex = columnIndex - 1}, // topLeft
    };

    for (const auto& cell : neighbors) {
        if (cell.rowIndex >= 0 && cell.rowIndex < numRows && cell.columnIndex >= 0 && cell.columnIndex < numColumns) {
            auto neighborCharacter = input[cell.rowIndex][cell.columnIndex];
            if (neighborCharacter != SYMBOL_EMPTY && !std::isdigit(neighborCharacter)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::vector<std::string> lines = getInputLines("./input.txt");
    
    std::string partString { "" };
    bool isValidPartNumber { false };
    int partNumberSum = { 0 };

    for (size_t rowIndex = 0; rowIndex < lines.size(); rowIndex++) {
        const auto& line = lines[rowIndex];

        for (size_t columnIndex = 0; columnIndex < line.length(); columnIndex++) {
            auto character = line[columnIndex];
            if (std::isdigit(character)) {
                partString += character;
                // Keep track of this as we look at every digit; short-circuit if we already set it to true
                if (!isValidPartNumber && hasNeighboringSymbol(lines, rowIndex, columnIndex)) {
                    isValidPartNumber = true;
                }
            } else {
                // We assembled a part number
                if (isValidPartNumber && partString.size()) {
                    int partNumber = std::stoi(partString);
                    partNumberSum += partNumber;
                }
                // Reset for next number
                partString = "";
                isValidPartNumber = false;
            }
        }
    }

    std::cout << "Answer: " << partNumberSum << std::endl;
    return 0;
}
