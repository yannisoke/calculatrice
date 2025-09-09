#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include "calculator.hpp"

// Détecte si la ligne commence par une commande reconnue (add, mul, sub, div)
bool isCommandLine(const std::string& line);

// Évalue une commande préfixée (ex: "add 1 2 3")
// Retourne CalcResult (success=false si erreur)
CalcResult evaluateCommand(const std::string& line);

#endif