#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <sys/types.h>
#include <vector>
#include "../utils.h"

#define SYMBOL_GEAR '*'
#define MAX_NUM_PART_NUMBERS_PER_GEAR 2

struct Cell {
    size_t rowIndex { 0 };
    size_t columnIndex { 0 };
};

struct Number {
    Cell location { 0, 0 };
    std::string value { "" };
};

int main() {
    std::vector<std::string> lines = getInputLines("./input.txt");
    std::vector<Number> numbers { };
    std::vector<Cell> gears { };
    // Used to build up numbers from digits while looping over input
    std::string numberAsString { "" };

    // Track locations of all numbers and gears in a single pass
    for (size_t rowIndex = 0; rowIndex < lines.size(); rowIndex++) {
        const auto& line = lines[rowIndex];

        for (size_t columnIndex = 0; columnIndex < line.length(); columnIndex++) {
            const auto& character = line[columnIndex];

            // We're looking at a digit, so it must belong to a number
            if (std::isdigit(character)) {
                // We're looking at the first digit of a new number, so let's keep track of the number's starting location
                if (!numberAsString.length()) {
                    numbers.push_back({ .location = { rowIndex, columnIndex } });
                }
                // And build up the number string one digit at a time
                numberAsString += character;
            } else {
                // Found a gear. Remember its location.
                if (character == SYMBOL_GEAR) {
                    gears.push_back({ .rowIndex = rowIndex, .columnIndex = columnIndex });
                }
                // We had a number in progress when we encountered this non-digit character, so we're done with that number. Commit its value.
                if (numberAsString.length()) {
                    // Remember number value as a string so we can easily read its length later. We'll convert it to an int eventually.
                    numbers[numbers.size() - 1].value = numberAsString;
                    numberAsString = "";
                }
            }
        }
    }


    /*
        Example:

        .123........................
        ....*.......................
        ......567...................
        ....89......................

        If a gear and number are adjacent, |rowIndexDifference| <= 1. Moreover, for at least one 
        digit in the number, it must also be true that |columnIndexDifference| <= 1.

        In this example, only 123 is adjacent to the gear (*). 567 is 2 columns away; 89 is 2 rows away.

        NOTE: It would be more efficient to parse the input and, upon finding a gear, look at the current row,
        the previous row, and the next row. But this works.
    */
    int gearRatioSum = 0;
    for (const auto& gear : gears) {
        std::vector<int> adjacentPartNumbers { };
        for (const auto& number : numbers) {
            auto rowIndexDifference = abs((int)gear.rowIndex - (int)number.location.rowIndex);
            // This number is too far away vertically to be associated with the current gear, so ignore it.
            if (rowIndexDifference > 1) continue;

            // Check absolute column index difference between every digit in the number and the gear location.
            // If any difference is <= 1, they're associated. Otherwise, the number is too far away horizontally.
            size_t numberLastColumnIndex = number.location.columnIndex + number.value.length() - 1;
            for (auto columnIndex = number.location.columnIndex; columnIndex <= numberLastColumnIndex; columnIndex++) {
                auto columnIndexDifference = abs((int)gear.columnIndex - (int)columnIndex);

                // This digit (and therefore the whole number) is close enough horizontally to the gear to be associated with it
                if (columnIndexDifference <= 1) {
                    adjacentPartNumbers.push_back(std::stoi(number.value));
                    // No need to check the rest of the digits in the number
                    break;
                }
            }
        }
        if (adjacentPartNumbers.size() == MAX_NUM_PART_NUMBERS_PER_GEAR) {
            // Per problem statement, we multiply all individual numbers to get the current gear's ratio
            int gearRatio = std::accumulate(adjacentPartNumbers.begin(), adjacentPartNumbers.end(), 1, [](int product, int partNumber) {
                return product * partNumber;
            });
            // And then just add up all gear ratios
            gearRatioSum += gearRatio;
        }
    }

    std::cout << "Answer: " << gearRatioSum << std::endl;
    return 0;
}
