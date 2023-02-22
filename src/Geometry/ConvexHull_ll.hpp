vector<pll> convex_hull_ll(vector<pll> p) {
    rearrange(p);
    int n = sz(p), k = 0;
    if (n == 1) return p;
    vector<pll> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2) {
            ll x1 = ch[k - 1].first - ch[k - 2].first, y1 = ch[k - 1].second - ch[k - 2].second;
            ll x2 = p[i].first - ch[k - 1].first, y2 = p[i].second - ch[k - 1].second;
            if (x1 * y2 - x2 * y1 > 0) break;
            k--;
        }
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t) {
            ll x1 = ch[k - 1].first - ch[k - 2].first, y1 = ch[k - 1].second - ch[k - 2].second;
            ll x2 = p[i].first - ch[k - 1].first, y2 = p[i].second - ch[k - 1].second;
            if (x1 * y2 - x2 * y1 > 0) break;
            k--;
        }
    }
    ch.resize(k - 1);
    return ch;
}