#ifndef HISTORY_HPP
#define HISTORY_HPP

#include <string>
#include <vector>

class History {
public:
    // Charger depuis un fichier (si existe). Retourne true si ok ou fichier inexistant.
    bool loadFromFile(const std::string& path);

    // Sauver dans un fichier (écrase). Retourne true si ok.
    bool saveToFile(const std::string& path) const;

    // Ajouter une ligne valide (ex: "3 + 5 = 8")
    void add(const std::string& line);

    // Effacer tout
    void clear();

    // Récupérer toutes les lignes
    const std::vector<std::string>& all() const;

private:
    std::vector<std::string> entries_;
};

#endif