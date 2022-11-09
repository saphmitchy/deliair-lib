#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i = 0; i < int(n); i++)
#define per(i,n) for(int i = (n) - 1; 0 <= i; i--)
#define rep2(i,l,r) for(int i = (l); i < int(r); i++)
#define per2(i,l,r) for(int i = (r) - 1; int(l) <= i; i--)
#define MM << " " <<
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sz(x) (int)x.size()

template <typename T>
void print(const vector<T> &v, T x = 0) {
    int n = v.size();
    for (int i = 0; i < n; i++) cout << v[i] + x << (i == n - 1 ? '\n' : ' ');
    if (v.empty()) cout << '\n';
}

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

template <typename T>
bool chmax(T &x, const T &y) {
    return (x < y) ? (x = y, true) : false;
}

template <typename T>
bool chmin(T &x, const T &y) {
    return (x > y) ? (x = y, true) : false;
}

// const ll MOD = 1'000'000'007;
const ll MOD = 998'244'353;

//////////////////////////////////////////////////////////

template <class T>
using minheap = priority_queue<T, vector<T>, greater<T>>;
template <class T>
using maxheap = priority_queue<T>;

template <typename T>
int lb(const vector<T> &v, T x) {
    return lower_bound(begin(v), end(v), x) - begin(v);
}

template <typename T>
int ub(const vector<T> &v, T x) {
    return upper_bound(begin(v), end(v), x) - begin(v);
}

template <typename T>
void rearrange(vector<T> &v) {
    sort(begin(v), end(v));
    v.erase(unique(begin(v), end(v)), end(v));
}
