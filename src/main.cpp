#include <iostream>
#include <string>

#include "calculator.hpp"
#include "commands.hpp"
#include "history.hpp"
#include "colors.hpp"

static void printHelp() {
    const auto& c = colors();
    std::cout << colorIf(c.bold) << colorIf(c.yellow) << "Aide:\n" << colorIf(c.reset)
              << "  Expressions infixees : " << colorIf(c.cyan) << "3 + 5, 10 - 2, 8 * 4, 9 / 3, 10 % 3\n" << colorIf(c.reset)
              << "  Commandes prefixees  : " << colorIf(c.cyan) << "add 1 2 3, mul 2 3 4, sub 10 5 1, div 100 2 5\n" << colorIf(c.reset)
              << "  " << colorIf(c.magenta) << "history" << colorIf(c.reset) << "        : affiche l'historique\n"
              << "  " << colorIf(c.magenta) << "clearhistory" << colorIf(c.reset) << "  : efface l'historique\n"
              << "  " << colorIf(c.magenta) << "help" << colorIf(c.reset) << "           : cette aide\n"
              << "  " << colorIf(c.magenta) << "quit" << colorIf(c.reset) << "           : quitter\n";
}

int main() {
    // Déterminer si on active la couleur
    useColor() = terminalSupportsColor();

    const auto& c = colors();

    std::cout << colorIf(c.bold) << colorIf(c.green)
              << "Calculatrice CLI (Version enrichie)\n"
              << colorIf(c.reset);
    std::cout << "Tape '" << colorIf(c.magenta) << "help" << colorIf(c.reset)
              << "' pour l'aide, '" << colorIf(c.magenta) << "quit" << colorIf(c.reset)
              << "' pour quitter.\n";

    History history;
    const std::string historyFile = "data/history.txt";

    // S'assure que le dossier data existe (optionnel simple)
    // On ne fait rien si échec (ex: pas de permission), l’historique restera en mémoire
    {
        FILE* f = std::fopen(historyFile.c_str(), "a");
        if (f) std::fclose(f);
    }

    history.loadFromFile(historyFile);

    std::string line;
    while (true) {
        std::cout << colorIf(c.cyan) << "> " << colorIf(c.reset);
        if (!std::getline(std::cin, line)) {
            std::cout << "\n" << colorIf(c.yellow) << "Fin de l'entree. Sauvegarde et sortie.\n" << colorIf(c.reset);
            break;
        }

        if (line == "quit") {
            std::cout << colorIf(c.yellow) << "Sauvegarde de l'historique...\n" << colorIf(c.reset);
            if (!history.saveToFile(historyFile)) {
                std::cout << colorIf(c.red) << "[Attention] Echec de sauvegarde " << historyFile << "\n" << colorIf(c.reset);
            }
            std::cout << colorIf(c.green) << "Au revoir !\n" << colorIf(c.reset);
            break;
        }
        if (line == "help") {
            printHelp();
            continue;
        }
        if (line == "history") {
            const auto& all = history.all();
            if (all.empty()) {
                std::cout << colorIf(c.yellow) << "(Historique vide)\n" << colorIf(c.reset);
            } else {
                std::cout << colorIf(c.magenta) << "-- Historique --\n" << colorIf(c.reset);
                for (size_t i = 0; i < all.size(); ++i) {
                    std::cout << colorIf(c.magenta) << i + 1 << ":" << colorIf(c.reset)
                              << " " << all[i] << "\n";
                }
            }
            continue;
        }
        if (line == "clearhistory") {
            history.clear();
            std::cout << colorIf(c.yellow) << "Historique efface.\n" << colorIf(c.reset);
            continue;
        }
        if (line.empty()) {
            continue;
        }

        CalcResult res;
        if (isCommandLine(line)) {
            res = evaluateCommand(line);
        } else {
            res = evaluateInfix(line);
        }

        if (res.success) {
            std::cout << colorIf(c.green) << "= " << res.value << colorIf(c.reset) << "\n";
            history.add(line + " = " + std::to_string(res.value));
        } else {
            std::cout << colorIf(c.red) << "[Erreur] " << res.errorMessage << colorIf(c.reset) << "\n"
                      << colorIf(c.yellow) << "(Tape 'help' si besoin.)" << colorIf(c.reset) << "\n";
        }
    }

    return 0;
}