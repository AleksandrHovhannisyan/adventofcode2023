#include <cctype>
#include <iostream>
#include <fstream>

int main() {
    int sum = 0;

	std::ifstream inputFile;
	inputFile.open("./input.txt");

	std::string line { "" };
	while (std::getline(inputFile, line)) {
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
	inputFile.close();
	return 0;
}
