#include "dsu.h"
#include <algorithm>

DSU::DSU(int n) : p(n), r(n, 0) {
    for (int i = 0; i < n; ++i) p[i] = i;
}

int DSU::find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

bool DSU::unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (r[a] < r[b]) std::swap(a, b);
    p[b] = a;
    if (r[a] == r[b]) r[a]++;
    return true;
}

bool DSU::same(int a, int b) {
    return find(a) == find(b);
}
