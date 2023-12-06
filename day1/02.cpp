#include <cctype>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <utility>

int main() {
    std::ifstream inputFile;
    inputFile.open("./input.txt");

    int sum = 0;

    std::vector<std::pair<std::regex, std::string>> regexes = {
        // Numbers that bleed into each other at boundary
        {std::regex ("oneight"), "18"},
        {std::regex ("twone"), "21"},
        {std::regex ("threeight"), "38"},
        {std::regex ("fiveight"), "58"},
        {std::regex ("sevenine"), "79"},
        {std::regex ("eightwo"), "82"},
        {std::regex ("eightree"), "83"},
        {std::regex ("nineight"), "98"},

        // Lone numbers
        {std::regex ("one"),"1"},
        {std::regex ("two"),"2"},
        {std::regex ("three"),"3"},
        {std::regex ("four"),"4"},
        {std::regex ("five"),"5"},
        {std::regex ("six"),"6"},
        {std::regex ("seven"),"7"},
        {std::regex ("eight"),"8"},
        {std::regex ("nine"),"9"},
    };

    std::string line { "" };
    while (std::getline(inputFile, line)) {
        int firstDigit = -1;
        int lastDigit = -1;

        // Pre-process the string before searching for digits
        std::cout << "Line before replacements: " << line << "\n";
        for (const auto& regexMapping : regexes) {
            auto regex = regexMapping.first;
            auto replacement = regexMapping.second;
            line = std::regex_replace(line, regex, replacement);
        }
        std::cout << "Line after replacements: " << line << "\n";

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
