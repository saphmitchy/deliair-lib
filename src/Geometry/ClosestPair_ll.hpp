// 距離の 2 乗を求める

ll closest_pair_ll(vector<pll> p) {
    ll INF = 6e18;
    int n = sz(p);
    if (n == 0) return INF;
    sort(all(p));
    vector<pll> me(n);

    function<ll(int, int)> rec = [&](int l, int r) {
        if (r - l == 1) return INF;
        int m = (l + r) / 2;
        ll x = p[m].first;
        ll ret = min(rec(l, m), rec(m, r));
        inplace_merge(begin(p) + l, begin(p) + m, begin(p) + r, [](pll p1, pll p2) {
            if (p1.second != p2.second) return p1.second < p2.second;
            return p1.first < p2.first;
        });
        int cnt = 0;
        rep2(i, l, r) {
            ll d = p[i].first - x;
            if (d * d >= ret) continue;
            rep(j, cnt) {
                ll dx = p[i].first - me[cnt - j - 1].first;
                ll dy = p[i].second - me[cnt - j - 1].second;
                if (dy * dy >= ret) break;
                ret = min(ret, dx * dx + dy * dy);
            }
            me[cnt++] = p[i];
        }
        return ret;
    };

    return rec(0, n);
}