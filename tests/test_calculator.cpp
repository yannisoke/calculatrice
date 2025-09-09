#include "calculator.hpp"
#include "commands.hpp"
#include <cassert>
#include <iostream>

static void testInfix() {
    {
        auto r = evaluateInfix("3 + 5");
        assert(r.success && r.value == 8.0);
    }
    {
        auto r = evaluateInfix("10 / 2");
        assert(r.success && r.value == 5.0);
    }
    {
        auto r = evaluateInfix("10 % 3");
        assert(r.success && r.value == 1.0);
    }
    {
        auto r = evaluateInfix("5 / 0");
        assert(!r.success);
    }
}

static void testCommands() {
    {
        auto r = evaluateCommand("add 1 2 3");
        assert(r.success && r.value == 6.0);
    }
    {
        auto r = evaluateCommand("mul 2 3 4");
        assert(r.success && r.value == 24.0);
    }
    {
        auto r = evaluateCommand("sub 10 5 1");
        assert(r.success && r.value == 4.0);
    }
    {
        auto r = evaluateCommand("div 100 2 5");
        assert(r.success && r.value == 10.0);
    }
}

int main() {
    testInfix();
    testCommands();
    std::cout << "Tous les tests ont reussi.\n";
    return 0;
}