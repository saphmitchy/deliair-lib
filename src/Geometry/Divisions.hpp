// O(N^2log(N))

#define re(x) real(x)
#define im(x) imag(x)

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
    return P(re(p) * d, im(p) * d);
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
    return os << re(p) << ' ' << im(p);
}

bool cp_x(P p, P q) {
    if (!eq(re(p), re(q)))
        return re(p) < re(q);
    return im(p) < im(q);
}

bool cp_y(P p, P q) {
    if (!eq(im(p), im(q)))
        return im(p) < im(q);
    return re(p) < re(q);
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
    return re(p) * re(q) + im(p) * im(q);
}

R det(P p, P q) {
    return re(p) * im(q) - im(p) * re(q);
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

bool inter(L l, P p) { // 交点を持つか判定
    return abs(ccw(l.a, l.b, p)) != 1;
}

bool inter(L l, L m) {
    if (!eq(det(l.b - l.a, m.b - m.a), 0.0))
        return true;
    return eq(det(l.b - l.a, m.b - l.a), 0.0);
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
                lp[i].eb(sz(ps)), lp[j].eb(sz(ps));
                ps.eb(p);
            }
        }
    }
    int n = sz(ps);
    struct E {
        int to, no;
        R g, rg;
        E(int to, int no, R g, R rg) : to(to), no(no), g(g), rg(rg) {}
        bool operator<(E e) const {
            return g < e.g;
        }
    };
    vector<int> id(n, -1);
    vector<vector<E>> li(n);
    int cnt = 0;
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
            auto d = ps[q[i + 1]] - ps[q[i]];
            R g = atan2(im(d), re(d)), rg = atan2(-im(d), -re(d));
            li[q[i]].eb(q[i + 1], cnt, g, rg);
            li[q[i]].eb(q[i + 1], cnt++, g + pi * 2, rg);
            li[q[i + 1]].eb(q[i], cnt, rg, g);
            li[q[i + 1]].eb(q[i], cnt++, rg + pi * 2, g);
        }
    }
    rep(i, n) sort(all(li[i]));
    vector<bool> u(cnt, false);
    vector<VP> ret;
    rep(i, n) {
        each(l, li[i]) {
            if (u[l.no])
                continue;
            VP nv;
            auto nl = l;
            while (1) {
                nv.eb(ps[nl.to]);
                u[nl.no] = true;
                nl = *(upper_bound(all(li[nl.to]), E(-1, -1, nl.rg + EPS, -1)));
                if (nl.no == l.no)
                    break;
            }
            ret.eb(nv);
        }
    }
    return ret;
}