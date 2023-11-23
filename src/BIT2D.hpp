#pragma once
#include "template.hpp"

// C は座標の型
template <typename T, typename C>
struct BIT2D {
    int n;
    vector<C> xs;
    vector<pair<C, C>> allPoints;
    vector<vector<C>> ys;
    vector<BIT<T>> bits;

    BIT2D() {}

    void insert(C x, C y) {
        xs.eb(x);
        allPoints.eb(x, y);
    }

    void build() {
        rearrange(xs);
        n = sz(xs);
        ys.resize(n + 1);
        for (auto [x, y] : allPoints) {
            int i = lb(xs, x);
            for (i++; i <= n; i += (i & -i)) ys[i].eb(y);
        }
        rep(i, n + 1) {
            rearrange(ys[i]);
            bits.eb(sz(ys[i]), 0);
        }
    }

    void add(C x, C y, T a) {
        int i = lb(xs, x);
        for (i++; i <= n; i += (i & -i)) {
            int j = lb(ys[i], y);
            bits[i].add(j, a);
        }
    }

    T sum(C x, C ly, C ry) {
        int i = lb(xs, x);
        T ret = 0;
        for (; i > 0; i -= (i & -i)) {
            int lj = lb(ys[i], ly);
            int rj = lb(ys[i], ry);
            ret += bits[i].query(lj, rj);
        }
        return ret;
    }

    T query(C lx, C rx, C ly, C ry) { return sum(rx, ly, ry) - sum(lx, ly, ry); }
};
