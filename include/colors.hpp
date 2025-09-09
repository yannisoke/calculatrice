#ifndef COLORS_HPP
#define COLORS_HPP

#include <string>

#if defined(_WIN32)
// Sur Windows 10+, les séquences ANSI fonctionnent si le mode VT est activé.
// Pour rester simple ici, on suppose un terminal compatible (Git Bash, Windows Terminal, etc.).
// Sinon on pourrait ajouter une fonction pour activer ENABLE_VIRTUAL_TERMINAL_PROCESSING.
#endif

struct ColorSet {
    std::string reset;
    std::string red;
    std::string green;
    std::string yellow;
    std::string cyan;
    std::string magenta;
    std::string bold;
};

inline const ColorSet& colors() {
    static ColorSet set = {
        "\033[0m",
        "\033[31m",
        "\033[32m",
        "\033[33m",
        "\033[36m",
        "\033[35m",
        "\033[1m"
    };
    return set;
}

// Gestion simple d’activation/désactivation
inline bool terminalSupportsColor();

// Variable globale contrôlant l’usage réel (configurée au démarrage)
inline bool& useColor() {
    static bool flag = true;
    return flag;
}

#include <cstdlib>

#if defined(_WIN32)
  #include <io.h>
  #define ISATTY _isatty
  #define FILENO _fileno
#else
  #include <unistd.h>
  #define ISATTY isatty
  #define FILENO fileno
#endif

inline bool terminalSupportsColor() {
    if (std::getenv("NO_COLOR")) return false;
    if (std::getenv("FORCE_COLOR")) return true;
    return ISATTY(FILENO(stdout));
}

// Helpers
inline std::string colorIf(const std::string& code) {
    return useColor() ? code : "";
}

#endif