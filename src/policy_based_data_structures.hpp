#pragma once
#include "template.hpp"

// 共通
#include <bits/extc++.h>
using namespace __gnu_pbds;

// k 番目の要素の取得、x 未満の要素の個数の取得 ができる set
TT using Set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // Set<T> が set<T> と同じように使える

// 使用例
// Set<int> s;
// s.insert(3); ->{3}
// s.insert(2); ->{2,3}
// s.insert(5); ->{2,3,5}
// find_by_order(k) で k 番目(0-indexed)の値のイテレータを返す
// cout << *s.find_by_order(2) << endl; -> 5
// s.erase(3); ->{2,5}
// cout << *s.find_by_order(1) << endl; -> 5
// order_of_key(x) で x 未満の要素の個数を返す
// cout << s.order_of_key(4) << endl; -> 1

// TT using Set = tree<T, null_type, greater<T>, rb_tree_tag, tree_order_statistics_node_update>; // 降順



// gp_hash_table (std::unordered_map より 4 倍くらい速い unordered_map)
// テンプレート引数は std::unordered_map と同じなので特に typedef する必要はない
// 使い方も std::unordered_map とほぼ同じ

// 使用例
// gp_hash_table<int, int> m;
// m[3] = 5;
// m[2] = 1;
// cout << m[3] << endl; -> 5