#pragma once

#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define per(i, n) for (int i = (n)-1; i >= 0; i--)
#define rep2(i, l, r) for (int i = (l); i < (r); i++)
#define per2(i, l, r) for (int i = (r)-1; i >= (l); i--)
#define MM << " " <<
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)x.size()
#define each(e, x) for (auto &e : x)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
void print(vector<T> v, T x = 0) {
    int n = sz(v);
    rep(i, n) cout << v[i] + x << (i == n - 1 ? '\n' : ' ');
    if (n == 0) cout << '\n';
}

template <typename T>
void printn(vector<T> v, T x = 0) {
    int n = sz(v);
    rep(i, n) cout << v[i] + x << '\n';
}

template <typename T>
bool chmax(T &x, const T &y) {
    return (x < y) ? (x = y, true) : false;
}

template <typename T>
bool chmin(T &x, const T &y) {
    return (x > y) ? (x = y, true) : false;
}

template <class T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using maxheap = priority_queue<T>;

template <typename T>
int lb(vector<T> &v, T x) {
    return lower_bound(all(v), x) - begin(v);
}

template <typename T>
int ub(vector<T> &v, T x) {
    return upper_bound(all(v), x) - begin(v);
}

template <typename T>
void rearrange(vector<T> &v) {
    sort(all(v));
    v.erase(unique(all(v)), end(v));
}

struct io_setup {
    io_setup() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout << fixed << setprecision(15);
    }
} io_setup;

// const ll MOD = 1'000'000'007;
const ll MOD = 998244353;
