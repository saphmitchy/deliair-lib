#define COMPLEX 1

#include "../src/UnionFind.hpp"

int main() {
    UnionFind uf(6);
    assert(!uf.same(4, 1));
    assert(uf.unite(4, 1));
    assert(uf.same(4, 1));
    assert(!uf.same(4, 5));
    assert(uf.unite(5, 1));
    assert(uf.same(4, 5));
    assert(!uf.unite(4, 5));
    assert(!uf.same(2, 0));
    assert(uf.unite(2, 0));
    assert(uf.same(2, 0));
    assert(uf.size(1) == 3);
    assert(uf.size(3) == 1);
    assert(uf.size(0) == 2);
    assert(uf.count() == 3);
    auto g = uf.groups();
    for(auto &i : g) sort(all(i));
    sort(all(g));
    assert(g[0] == vector<int>({0, 2}));
    assert(g[1] == vector<int>({1, 4, 5}));
    assert(g[2] == vector<int>({3}));
}
