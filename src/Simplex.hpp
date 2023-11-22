#pragma once
#include "template.hpp"

// Maximize cx s.t. Ax <= b, x >= 0
// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html
// Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp
template <typename Float = double, int LOGEPS = 20>
struct Simplex {
    const Float EPS = 1.0 / (1LL << LOGEPS);
    int n, m;
    vector<int> shuffle_idx;
    vector<int> idx;
    vector<vector<Float>> mat;
    int i_ch, j_ch;

    void _initialize(vector<vector<Float>> A, vector<Float> b, vector<Float> c) {
        n = sz(c), m = sz(A);

        mat.assign(m + 2, vector<Float>(n + 2));
        i_ch = m;
        rep(i, m) {
            rep(j, n) mat[i][j] = -A[i][j];
            mat[i][n] = 1, mat[i][n + 1] = b[i];
            if (mat[i_ch][n + 1] > mat[i][n + 1]) i_ch = i;
        }
        rep(j, n) mat[m][j] = c[j];
        mat[m + 1][n] = -1;

        idx.resize(n + m + 1);
        iota(all(idx), 0);
    }

    void _solve() {
        vector<int> jupd;
        for (nb_iter = 0, j_ch = n;; nb_iter++) {
            if (i_ch < m) {
                swap(idx[j_ch], idx[i_ch + n + 1]);
                mat[i_ch][j_ch] = 1.0 / mat[i_ch][j_ch];
                jupd.clear();
                rep(j, n + 2) {
                    if (j != j_ch) {
                        mat[i_ch][j] *= -mat[i_ch][j_ch];
                        if (abs(mat[i_ch][j]) > EPS) jupd.eb(j); // abs() の括弧の位置に要注意
                    }
                }
                rep(i, m + 2) {
                    if (abs(mat[i][j_ch]) < EPS || i == i_ch) continue; // abs() の括弧の位置に要注意
                    each(j, jupd) mat[i][j] += mat[i][j_ch] * mat[i_ch][j];
                    mat[i][j_ch] *= mat[i_ch][j_ch];
                }
            }

            j_ch = -1;
            rep(j, n + 1) {
                if (j_ch < 0 || idx[j_ch] > idx[j]) {
                    if (mat[m + 1][j] > EPS || (abs(mat[m + 1][j]) < EPS && mat[m][j] > EPS)) j_ch = j; // abs() の括弧の位置に要注意
                }
            }
            if (j_ch < 0) break;

            i_ch = -1;
            rep(i, m) {
                if (mat[i][j_ch] < -EPS) {
                    if (i_ch < 0) {
                        i_ch = i;
                    } else if (mat[i_ch][n + 1] / mat[i_ch][j_ch] - mat[i][n + 1] / mat[i][j_ch] < -EPS) {
                        i_ch = i;
                    } else if (mat[i_ch][n + 1] / mat[i_ch][j_ch] - mat[i][n + 1] / mat[i][j_ch] < EPS && idx[i_ch] > idx[i]) {
                        i_ch = i;
                    }
                }
            }

            if (i_ch < 0) {
                is_infty = true;
                break;
            }
        }

        if (mat[m + 1][n + 1] < -EPS) {
            infeasible = true;
            return;
        }
        x.assign(n, 0);
        rep(i, m) {
            if (idx[n + 1 + i] < n) x[idx[n + 1 + i]] = mat[i][n + i];
        }
        ans = mat[m][n + 1];
    }

    unsigned nb_iter;
    bool is_infty;
    bool infeasible;
    vector<Float> x;
    Float ans;

    Simplex(vector<vector<Float>> A, vector<Float> b, vector<Float> c) {
        is_infty = infeasible = false;
        _initialize(A, b, c);
        _solve();
    }
};
