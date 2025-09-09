# Calculatrice CLI Évolutive (Version enrichie)

Objectif : Apprendre le C++ progressivement (lecture entrée, parsing simple, séparation en fichiers, commandes).

## Fonctionnalités

- Expressions infixées : `3 + 5`, `10 / 2`, `8 * 4`, `10 % 3`
- Commandes préfixées multi-opérandes :
  - `add 1 2 3` → 6
  - `mul 2 3 4` → 24
  - `sub 10 5 1` → 4 (calcul = (((10 - 5) - 1)) )
  - `div 100 2 5` → 10 (calcul = ((100 / 2) / 5))
- Historique :
  - `history` → liste des calculs réussis
  - `clearhistory` → purge en mémoire
  - Sauvegarde automatique dans `data/history.txt`
- Aide : `help`
- Quitter : `quit`

## Arborescence

```
projet-calculatrice/
  CMakeLists.txt
  README.md
  include/
    calculator.hpp
    commands.hpp
    history.hpp
  src/
    main.cpp
    calculator.cpp
    commands.cpp
    history.cpp
  tests/
    test_calculator.cpp
  data/
    (history.txt sera créé à la première sauvegarde)
  build/ (généré)
```

## Compilation avec CMake

```
mkdir -p build
cd build
cmake ..
cmake --build .
./calculatrice
```

Sous Windows (PowerShell + MinGW) :

```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
./calculatrice.exe
```

## Compilation rapide sans CMake (Linux/macOS)

```
g++ -std=c++17 -Wall -Wextra -pedantic -O2 -o calculatrice \
    src/main.cpp src/calculator.cpp src/commands.cpp src/history.cpp -I include
./calculatrice
```

## Exemples d’utilisation

```
> 3 + 5
= 8
> add 1 2 3 4
= 10
> mul 2 3 4
= 24
> sub 10 5 1
= 4
> div 100 2 5
= 10
> history
1: 3 + 5 = 8.000000
2: add 1 2 3 4 = 10.000000
...
> quit
Sauvegarde de l'historique...
Au revoir !
```

## Idées d’améliorations futures

- Support décimales dans history formaté (`std::format` ou `fmt`).
- Couleurs (lib `fmt`).
- Parenthèses dans infix (nécessiterait un vrai parseur).
- Tests unitaires plus nombreux (Cas erreurs).
- Option : sauvegarder uniquement les résultats (JSON).
