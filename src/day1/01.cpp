#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include "../utils.h"

int main() {
    int sum = 0;

    std::vector<std::string> lines = getInputLines("./input.txt");

    for (const auto& line : lines) {
        int firstDigit = -1;
        int lastDigit = -1;

        for (auto character : line) {
            if (isdigit(character)) {
                int digit = character - '0';
                // Only set the first digit the first time we encounter it
                if (firstDigit == -1) {
                    firstDigit = digit;
                }
                // But always keep track of the last seen digit
                lastDigit = digit;
            }
        }
        // Instead of concatenating the two digits and converting to an int
        sum += firstDigit * 10 + lastDigit;
    }

    std::cout << "Answer: " << sum << std::endl;
    return 0;
}
