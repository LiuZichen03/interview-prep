#pragma once
#include <vector>

struct DSU {
    std::vector<int> p, r;
    explicit DSU(int n);
    int find(int x);
    bool unite(int a, int b);
    bool same(int a, int b);
};
