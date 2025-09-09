#include "calculator.hpp"
#include <sstream>
#include <cctype>
#include <string>

// Trim simple
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }
    return s.substr(start, end - start);
}

CalcResult evaluateInfix(const std::string& lineRaw) {
    std::string line = trim(lineRaw);
    if (line.empty()) {
        return {false, 0.0, "Ligne vide"};
    }

    std::istringstream iss(line);
    double a = 0.0;
    double b = 0.0;
    char op = 0;

    if (!(iss >> a)) {
        return {false, 0.0, "Nombre gauche invalide"};
    }
    if (!(iss >> op)) {
        return {false, 0.0, "Opérateur manquant"};
    }
    if (!(iss >> b)) {
        return {false, 0.0, "Nombre droit invalide"};
    }

    // Vérifie s'il y a du surplus
    std::string extra;
    if (iss >> extra) {
        return {false, 0.0, "Caractères supplémentaires"};
    }

    double result = 0.0;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/':
            if (b == 0.0) return {false, 0.0, "Division par zéro"};
            result = a / b;
            break;
        case '%': {
            // Modulo sur parties entières
            int ia = static_cast<int>(a);
            int ib = static_cast<int>(b);
            if (ib == 0) return {false, 0.0, "Modulo par zéro"};
            result = static_cast<double>(ia % ib);
            break;
        }
        default:
            return {false, 0.0, "Opérateur inconnu (+ - * / %)"};
    }

    return {true, result, ""};
}