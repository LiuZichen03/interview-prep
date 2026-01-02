#include <iostream>
#include "dsu.h"

int main() {
    DSU dsu(5);
    dsu.unite(0, 1);
    dsu.unite(3, 4);
    std::cout << (dsu.same(0, 1) ? "yes" : "no") << "\n";
    std::cout << (dsu.same(1, 2) ? "yes" : "no") << "\n";
    return 0;
}
