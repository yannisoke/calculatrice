#include "history.hpp"
#include <fstream>

bool History::loadFromFile(const std::string& path) {
    entries_.clear();
    std::ifstream in(path);
    if (!in.is_open()) {
        // Ce n'est pas une erreur si le fichier n'existe pas encore
        return true;
    }
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) entries_.push_back(line);
    }
    return true;
}

bool History::saveToFile(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out.is_open()) return false;
    for (const auto& e : entries_) {
        out << e << "\n";
    }
    return true;
}

void History::add(const std::string& line) {
    entries_.push_back(line);
}

void History::clear() {
    entries_.clear();
}

const std::vector<std::string>& History::all() const {
    return entries_;
}