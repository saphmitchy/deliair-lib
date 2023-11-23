#pragma once
#include "template.hpp"
#include "SegmentTree.hpp"

// C は座標の型
template <typename T, typename C>
struct SegmentTree2D {
    using F = function<T(T, T)>;
    int n;
    vector<C> xs;
    vector<pair<C, C>> allPoints;
    vector<vector<pair<C, C>>> points;
    vector<SegmentTree<T>> segs;
    F f;
    T e;

    SegmentTree2D(F f, T e) : f(f), e(e) {}

    void insert(C x, C y) {
        xs.eb(x);
        allPoints.eb(x, y);
    }

    void build() {
        rearrange(xs);
        int m = sz(xs);
        n = 1;
        while (n < m) n <<= 1;
        points.resize(2 * n);
        for (auto [x, y] : allPoints) {
            int i = lb(xs, x);
            i += n;
            while (i > 0) {
                points[i].eb(y, x);
                i >>= 1;
            }
        }
        rep(i, 2 * n) {
            rearrange(points[i]);
            segs.eb(sz(points[i]), e, f, e);
        }
    }

    void update(C x, C y, T a, bool apply = false) {
        int i = lb(xs, x);
        i += n;
        while (i > 0) {
            int j = lb(points[i], pair(y, x));
            segs[i].update(j, a, apply);
            i >>= 1;
        }
    }

    T query(C lx, C rx, C ly, C ry) {
        T L = e, R = e;
        int li = lb(xs, lx);
        int ri = lb(xs, rx);
        li += n, ri += n;
        C mi = empty(xs) ? 0 : xs[0];
        while (li < ri) {
            if (li & 1) {
                int l = lb(points[li], pair(ly, mi));
                int r = lb(points[li], pair(ry, mi));
                L = f(L, segs[li].query(l, r));
                li++;
            }
            if (ri & 1) {
                ri--;
                int l = lb(points[ri], pair(ly, mi));
                int r = lb(points[ri], pair(ry, mi));
                R = f(segs[ri].query(l, r), R);
            }
            li >>= 1, ri >>= 1;
        }
        return f(L, R);
    }
};