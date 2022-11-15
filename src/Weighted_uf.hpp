#pragma once

#include "template.hpp"

template<class T>
struct Weighted_uf {
    const int n;
    vector<int> data;
    vector<T> ws; // (自分の重み) - (親の重み)
    #if COMPLEX
    int cnt;
    #endif

    Weighted_uf(int _n) : n(_n), data(n, -1), ws(n, 0) {
        #if COMPLEX
        cnt = n;
        #endif
    }

    int root(int x) {
        if(data[x] < 0) return x;
        int par = root(data[x]);
        ws[x] += ws[data[x]];
        return data[x] = par;
    }

    int operator[](int i) { return root(i); }

    T weight(int x) {
        root(x);
        return ws[x];
    }


    // weight(x) - weghit(y) = w;
    // 
    bool unite(int x, int y, T w) {
        int a = root(x), b = root(y);
        w -= ws[x], w += ws[y];
        if(a == b) return w == 0;
        #if COMPLEX
        --cnt;
        data[b] += data[a];
        #endif
        data[a] = b;
        ws[a] = w;
        return true;
    }

    // weight(x) - weghit(y)
    T diff(int x, int y) { return weight(x) - weight(y); }

    bool same(int x, int y) { return root(x) == root(y); }

    // below functions are optional

    vector<vector<int>> groups() {
        vector<vector<int>> res(n);
        rep(i,n) res[root(i)].emplace_back(i);
        // 空集合を取り除く
        res.erase(remove_if(begin(res), end(res), [&](auto &v) { return v.empty();}), res.end());
        return res;
    }

    #if COMPLEX
    void clear() {
        cnt = n;
        fill(all(data), -1);
        fill(all(ws), 0);
    }

    int size(int x) { return -data[root(x)]; }

    int count() { return cnt; }
    #endif
};