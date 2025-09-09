#include "commands.hpp"
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>

static std::string toLower(std::string s) {
    for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

bool isCommandLine(const std::string& line) {
    std::istringstream iss(line);
    std::string first;
    if (!(iss >> first)) return false;
    first = toLower(first);
    return (first == "add" || first == "mul" || first == "sub" || first == "div");
}

static CalcResult foldCommand(const std::string& cmd, const std::vector<double>& nums) {
    if (nums.empty()) {
        return {false, 0.0, "Aucun nombre fourni"};
    }

    double acc = 0.0;
    if (cmd == "add") {
        acc = 0.0;
        for (double v : nums) acc += v;
    } else if (cmd == "mul") {
        acc = 1.0;
        for (double v : nums) acc *= v;
    } else if (cmd == "sub") {
        acc = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) acc -= nums[i];
    } else if (cmd == "div") {
        acc = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            if (nums[i] == 0.0) {
                return {false, 0.0, "Division par zéro dans la commande"};
            }
            acc /= nums[i];
        }
    } else {
        return {false, 0.0, "Commande inconnue"};
    }

    return {true, acc, ""};
}

CalcResult evaluateCommand(const std::string& line) {
    std::istringstream iss(line);
    std::string cmd;
    if (!(iss >> cmd)) {
        return {false, 0.0, "Ligne vide"};
    }
    cmd = toLower(cmd);

    std::vector<double> numbers;
    double value;
    while (iss >> value) {
        numbers.push_back(value);
    }

    if (numbers.empty()) {
        return {false, 0.0, "Aucun nombre à traiter"};
    }

    return foldCommand(cmd, numbers);
}