#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>

struct CalcResult {
    bool success;
    double value;
    std::string errorMessage;
};

// Évalue une expression de la forme "a op b" avec op dans + - * / %
CalcResult evaluateInfix(const std::string& line);

#endif