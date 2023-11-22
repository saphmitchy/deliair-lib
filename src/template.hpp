#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = (n)-1; i >= 0; i--)
#define rep2(i, l, r) for (int i = (l); i < (r); i++)
#define per2(i, l, r) for (int i = (r)-1; i >= (l); i--)
#define each(e, x) for (auto &e : x)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define eb emplace_back
#define MM << ' ' <<
#define TT template <typename T>
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

TT bool chmin(T &x, T y) { return x > y ? (x = y, true) : false; }

TT bool chmax(T &x, T y) { return x < y ? (x = y, true) : false; }

TT using minheap = priority_queue<T, vector<T>, greater<T>>;
TT using maxheap = priority_queue<T>;

TT void print(vector<T> v, T x = 0) {
    int n = sz(v);
    rep(i, n) cout << v[i] + x << (i == n - 1 ? '\n' : ' ');
    if (n == 0) cout << '\n';
}

TT void printn(vector<T> v, T x = 0) {
    int n = sz(v);
    rep(i, n) cout << v[i] + x << '\n';
}

TT void rearrange(vector<T> &v) {
    sort(all(v));
    v.erase(unique(all(v)), end(v));
}

TT int lb(vector<T> &v, T x) { return lower_bound(all(v), x) - begin(v); }

TT int ub(vector<T> &v, T x) { return upper_bound(all(v), x) - begin(v); }

const int inf = (1 << 30) - 1;
const ll INF = (1LL << 60) - 1;

struct io_setup {
    io_setup() {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout << fixed << setprecision(15);
    }
} io_setup;

// const ll MOD = 1'000'000'007;
const ll MOD = 998244353;
