#pragma once

// 型名
// R:Real, P:Point, L:Line, S:Segment, C:Circle, VP:vector<Point>

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