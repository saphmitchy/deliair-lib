#pragma once
#include "template.hpp"

// 型名
// R:Real, P:Point, L:Line, S:Segment, C:Circle, VP:vector<Point>

#define X(p) real(p)
#define Y(p) imag(p)

using R = double;
using P = complex<R>;
using VP = vector<P>;

const R EPS = 1e-6; // ここは適宜調節する
const R pi = acos(-1.0);

int sgn(R a) {
    return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0;
} // 符号関数

bool eq(R a, R b) {
    return sgn(b - a) == 0;
}

P operator*(P p, R d) {
    return P(X(p) * d, Y(p) * d);
}

P operator/(P p, R d) {
    return p * (1 / d);
}

istream &operator>>(istream &is, P &p) {
    // R a, b; // 入力が小数
    int a, b; // 入力が整数
    is >> a >> b;
    p = P(a, b);
    return is;
}

ostream &operator<<(ostream &os, P p) {
    return os << X(p) << ' ' << Y(p);
}

bool cp_x(P p, P q) {
    if (!eq(X(p), X(q)))
        return X(p) < X(q);
    return Y(p) < Y(q);
}

bool cp_y(P p, P q) {
    if (!eq(Y(p), Y(q)))
        return Y(p) < Y(q);
    return X(p) < X(q);
}

struct L {
    P a, b;
    L() {}
    L(P a, P b) : a(a), b(b) {}

    // 入出力（必要なら）
    friend ostream &operator<<(ostream &os, L &l) {
        return os << l.a << ' ' << l.b;
    }
    friend istream &operator>>(istream &is, L &l) {
        return is >> l.a >> l.b;
    }
};

struct S : L {
    S() {}
    S(P a, P b) : L(a, b) {}
};

struct C {
    P p;
    R r;
    C() {}
    C(P p, R r) : p(p), r(r) {}
};

P rot(P p, R t) {
    return p * P(cos(t), sin(t));
}

R dot(P p, P q) {
    return X(p) * X(q) + Y(p) * Y(q);
}

R det(P p, P q) {
    return X(p) * Y(q) - Y(p) * X(q);
}

int ccw(P a, P b, P c) { // 線分 ab に対する c の位置関係
    b -= a, c -= a;
    if (sgn(det(b, c)) == 1)
        return +1; // COUNTER_CLOCKWISE
    if (sgn(det(b, c)) == -1)
        return -1; // CLOCKWISE
    if (dot(b, c) < 0.0)
        return +2; // ONLINE_BACK
    if (norm(b) < norm(c))
        return -2; // ONLINE_FRONT
    return 0;      // ON_SEGMENT
}

bool para(L a, L b) { // 平行判定
    return eq(det(a.b - a.a, b.b - b.a), 0.0);
}

bool orth(L a, L b) { // 垂直判定
    return eq(dot(a.b - a.a, b.b - b.a), 0.0);
}

P proj(L l, P p) { // 垂線の足
    R t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
    return l.a + (l.b - l.a) * t;
}

// これいる？
// P proj(S s, P p) {
//     R t = dot(p - s.a, s.b - s.a) / norm(s.b - s.a);
//     return s.a + (s.b - s.a) * t;
// }

P refl(L l, P p) { // 線対称の位置にある点
    return p + (proj(l, p) - p) * 2.0;
}

bool inter(L l, P p) { // 交点を持つか判定
    return abs(ccw(l.a, l.b, p)) != 1;
}

bool inter(S s, P p) {
    return ccw(s.a, s.b, p) == 0;
}

bool inter(L l, L m) {
    if (!eq(det(l.b - l.a, m.b - m.a), 0.0))
        return true;
    return eq(det(l.b - l.a, m.b - l.a), 0.0);
}

bool inter(L l, S s) {
    return sgn(det(l.b - l.a, s.a - l.a) * det(l.b - l.a, s.b - l.a)) <= 0;
}

bool inter(S s, L l) {
    return inter(l, s);
}

bool inter(S s, S t) {
    if (ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) > 0)
        return false;
    return ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

R dist(P p, P q) {
    return abs(q - p);
}

R dist(L l, P p) {
    return abs(p - P(proj(l, p)));
}

R dist(S s, P p) {
    P h = proj(s, p);
    if (inter(s, h))
        return abs(h - p);
    return min(abs(s.a - p), abs(s.b - p));
}

R dist(L l, L m) {
    return inter(l, m) ? 0.0 : dist(l, m.a);
}

R dist(S s, S t) {
    if (inter(s, t))
        return 0.0;
    return min({dist(s, t.a), dist(s, t.b), dist(t, s.a), dist(t, s.b)});
}

R dist(L l, S s) {
    if (inter(l, s))
        return 0.0;
    return min(dist(l, s.a), dist(l, s.b));
}

R dist(S s, L l) {
    return dist(l, s);
}

bool inter(C c, L l) {
    return sgn(c.r - dist(l, c.p)) >= 0;
}

bool inter(C c, P p) {
    return eq(abs(p - c.p), c.r);
}

// 共通接線の本数
// 交点なし:4
// 外接:3
// 2点で交わる:2
// 内接:1
// 一方がもう一方を内包:0
int inter(C c1, C c2) {
    if (c1.r < c2.r)
        swap(c1, c2);
    R d = abs(c1.p - c2.p);
    int a = sgn(d - c1.r - c2.r);
    if (a >= 0)
        return 3 + a;
    return 1 + sgn(d - c1.r + c2.r);
}

VP crosspoint(L l, L m) {
    VP ret;
    if (!inter(l, m))
        return ret;
    R A = det(l.b - l.a, m.b - m.a);
    R B = det(l.b - l.a, l.b - m.a);
    if (eq(A, 0.0) && eq(B, 0.0)) {
        ret.eb(m.a);
    } else {
        ret.eb(m.a + (m.b - m.a) * B / A);
    }
    return ret;
}

VP crosspoint(S s, S t) {
    return inter(s, t) ? crosspoint(L(s), L(t)) : VP();
}

VP crosspoint(C c, L l) {
    P h = proj(l, c.p);
    P e = (l.b - l.a) / abs(l.b - l.a);
    VP ret;
    if (!inter(c, l))
        return ret;
    if (eq(dist(l, c.p), c.r)) {
        ret.eb(h);
    } else {
        R b = sqrt(c.r * c.r - norm(h - c.p));
        ret.push_back(h + e * b), ret.push_back(h - e * b);
    }
    return ret;
}

VP crosspoint(C c1, C c2) {
    R d = abs(c1.p - c2.p);
    R a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    R t = atan2(Y(c2.p) - Y(c1.p), X(c2.p) - X(c1.p));
    VP ret;
    if (inter(c1, c2) % 4 == 0) // 交わらないとき
        return ret;
    if (eq(a, 0.0)) {
        ret.eb(P(c1.p + rot(P(c1.r, 0.0), t)));
    } else {
        P p1 = c1.p + rot(P(c1.r, 0.0), t + a);
        P p2 = c1.p + rot(P(c1.r, 0.0), t - a);
        ret.eb(p1), ret.eb(p2);
    }
    return ret;
}

VP cut(VP p, L l, bool border = true) { // 直線が多角形に切り取られる区間
    int n = sz(p);
    p.eb(p[0]), p.eb(p[1]);
    VP ret;
    rep(i, n) {
        if (!eq(dist(l, p[i]), 0) && !eq(dist(l, p[i + 1]), 0)) {
            S s(p[i], p[i + 1]);
            if (eq(dist(l, s), 0)) {
                auto res = crosspoint(l, s);
                ret.eb(res[0]);
            }
        }
        if (eq(dist(l, p[i + 1]), 0)) {
            if ((eq(dist(l, p[i]), 0) || eq(dist(l, p[i + 2]), 0)) && !border)
                continue;
            S s(p[i], p[i + 2]);
            if (eq(dist(l, s), 0))
                ret.eb(p[i + 1]);
        }
    }
    return ret;
}

VP rectangle(S s, R r) { // sを軸とした幅rの長方形
    P d = (s.a - s.b) * P(0, 1);
    d *= r / sqrt(norm(d));
    return VP{s.a + d, s.a - d, s.b - d, s.b + d};
}

L vertical_bisector(P p, P q) { // 垂直二等分線
    L l;
    l.a = (p + q) * 0.5;
    l.b = l.a + rot(q - p, pi * 0.5);
    return l;
}

C Apollonius(P p, P q, R a, R b) { // アポロニウスの円
    P p1 = (p * b + q * a) / (a + b), p2 = (-p * b + q * a) / (a - b);
    C c;
    c.p = (p1 + p2) * 0.5;
    c.r = abs(p1 - p2) * 0.5;
    return c;
}

R area(VP p) { // 多角形の面積
    R ret = 0.0;
    int n = sz(p);
    rep(i, n) ret += det(p[i], p[(i + 1) % n]);
    return abs(ret * 0.5);
}

int in_polygon(VP p, P q) { // IN:2, ON:1, OUT:0
    int n = sz(p);
    int ret = 0;
    rep(i, n) {
        P a = p[i] - q, b = p[(i + 1) % n] - q;
        if (eq(det(a, b), 0.0) && sgn(dot(a, b)) <= 0)
            return 1;
        if (Y(a) > Y(b))
            swap(a, b);
        if (sgn(Y(a)) <= 0 && sgn(Y(b)) == 1 && sgn(det(a, b)) == 1)
            ret ^= 2;
    }
    return ret;
}

VP tangent(C c, P p) { // 点 p を通る円 c の接線と c の接点
    return crosspoint(c, C(p, sqrt(norm(p - c.p) - c.r * c.r)));
}

vector<L> tangent(C c1, C c2) { // 共通接線
    vector<L> ret;
    if (c1.r < c2.r)
        swap(c1, c2);
    R r = abs(c2.p - c1.p);
    if (eq(r, 0.0))
        return ret;
    P u = (c2.p - c1.p) / r;
    P v = rot(u, pi * 0.5);
    for (R s : {1.0, -1.0}) {
        R h = (c1.r + c2.r * s) / r;
        if (eq(abs(h), 1.0)) {
            ret.eb(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
        } else if (abs(h) < 1.0) {
            P uu = u * h, vv = v * sqrt(1.0 - h * h);
            ret.eb(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
            ret.eb(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
        }
    }
    return ret;
}

VP convex_hull(VP p) { // 凸包
    sort(all(p), cp_x);
    p.erase(unique(all(p)), end(p));
    int n = sz(p), k = 0;
    if (n == 1)
        return p;
    VP ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && sgn(det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= 0)
            k--;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && sgn(det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= 0)
            k--;
    }
    ch.resize(k - 1);
    return ch;
}

R closest_pair(VP p) { // 最近点対の距離
    if (sz(p) <= 1)
        return 1e18;
    sort(all(p), cp_x);
    VP memo(sz(p));

    function<R(int, int)> rec = [&](int l, int r) {
        if (r - l <= 1)
            return R(1e18);
        int m = (l + r) >> 1;
        R x = X(p[m]);
        R ret = min(rec(l, m), rec(m, r));
        inplace_merge(p.begin() + l, p.begin() + m, p.begin() + r, cp_y);
        int cnt = 0;
        rep2(i, l, r) {
            if (abs(X(p[i]) - x) >= ret)
                continue;
            rep(j, cnt) {
                P d = p[i] - memo[cnt - j - 1];
                if (Y(d) >= ret)
                    break;
                chmin(ret, abs(d));
            }
            memo[cnt++] = p[i];
        }
        return ret;
    };

    return rec(0, sz(p));
}

vector<VP> divisions(vector<L> lf, R lim = 1e9) {
    vector<L> ls;
    each(l, lf) {
        bool ok = true;
        each(m, ls) {
            if (para(l, m) & inter(l, m.a)) {
                ok = false;
                break;
            }
        }
        if (ok)
            ls.eb(l);
    }
    VP lc{P(-lim, -lim), P(lim, -lim), P(lim, lim), P(-lim, lim)};
    rep(i, 4) ls.eb(lc[i], lc[(i + 1) % 4]);
    int m = sz(ls);
    VP ps;
    vector<vector<int>> lp(m);
    rep(i, m) {
        rep2(j, i + 1, m) {
            each(p, crosspoint(ls[i], ls[j])) {
                if (max(abs(X(p)), abs(Y(p))) < lim + EPS) {
                    lp[i].eb(sz(ps)), lp[j].eb(sz(ps));
                    ps.eb(p);
                }
            }
        }
    }
    int n = sz(ps);
    vector<int> id(n, -1), to;
    vector<R> rg;
    vector<vector<pair<R, int>>> li(n);
    rep(i, m) {
        sort(all(lp[i]), [&ps](int a, int b) { return cp_x(ps[a], ps[b]); });
        vector<int> q;
        rep(j, sz(lp[i])) {
            int me = id[lp[i][j]], st = j;
            auto np = ps[lp[i][j]];
            while (j + 1 < sz(lp[i])) {
                if (abs(ps[lp[i][j + 1]] - np) < EPS) {
                    j++;
                    if (id[lp[i][j]] != -1)
                        me = id[lp[i][j]];
                } else
                    break;
            }
            if (me == -1)
                me = lp[i][st];
            rep2(k, st, j + 1) id[lp[i][k]] = me;
            q.eb(me);
        }
        rep(i, sz(q) - 1) {
            P d = ps[q[i + 1]] - ps[q[i]];
            R s = atan2(Y(d), X(d)), t = atan2(-Y(d), -X(d));
            int x = q[i], y = q[i + 1];
            li[x].eb(s, sz(to));
            li[x].eb(s + pi * 2, sz(to));
            to.eb(y), rg.eb(t);
            li[y].eb(t, sz(to));
            li[y].eb(t + pi * 2, sz(to));
            to.eb(x), rg.eb(s);
        }
    }
    rep(i, n) sort(all(li[i]));
    vector<bool> u(sz(to), false);
    vector<VP> ret;
    rep(i, n) {
        each(l, li[i]) {
            int ns = l.second;
            if (u[ns])
                continue;
            VP nv;
            int no = ns;
            bool ok = true;
            while (1) {
                if (sz(nv) > 1) {
                    P x = nv[sz(nv) - 2], y = nv[sz(nv) - 1], z = ps[to[no]];
                    int c = ccw(x, y, z);
                    if (c == 1)
                        ok = false;
                    if (c != -1)
                        nv.pop_back();
                }
                nv.eb(ps[to[no]]);
                u[no] = true;
                no = upper_bound(all(li[to[no]]), pair(rg[no] + EPS, -1))->second;
                if (no == ns)
                    break;
            }
            if (ok)
                ret.eb(nv);
        }
    }
    return ret;
}