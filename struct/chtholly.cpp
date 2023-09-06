#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5, P = 1e9 + 7;
int n, m, seed, p, a[N];
struct node {
    int l, r;
    mutable i64 val;
};
bool cmp(node a, node b) { return a.l < b.l; }
set<node, decltype(&cmp)> S(cmp);
vector<pair<i64, int>> A;
auto split(int x) {
    auto it = --S.upper_bound({x});
    if (it->l == x) return it;
    int l = it->l, r = it->r;
    i64 val = it->val;
    S.erase(it);
    S.insert({l, x - 1, val});
    return S.insert({x, r, val}).first;
}
void assign(int l, int r, int x) {
    auto ed = split(r + 1), st = split(l);
    S.erase(st, ed);
    S.insert({l, r, x});
}
void update(int l, int r, int x) {
    auto ed = split(r + 1), st = split(l);
    for (auto it = st; it != ed; ++it) it->val += x;
}
int quickpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}
int querysum(int l, int r, int x, int y) {
    auto ed = split(r + 1), st = split(l);
    int res = 0;
    for (auto it = st; it != ed; ++it)
        res = (res + (i64)quickpow(it->val % y, x, y) * (it->r - it->l + 1) % y) % y;
    return res;
}
i64 querykth(int l, int r, int x) {
    auto ed = split(r + 1), st = split(l);
    A.clear();
    for (auto it = st; it != ed; ++it) A.emplace_back(it->val, it->r - it->l + 1);
    sort(A.begin(), A.end());
    for (auto [val, cnt] : A)
        if ((x -= cnt) <= 0) return val;
    return numeric_limits<i64>::max();
}
int rnd() {
    int res = seed;
    seed = ((i64)seed * 7 + 13) % P;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> seed >> p;
    for (int i = 1; i <= n; ++i) {
        a[i] = (rnd() % p) + 1;
        S.insert({i, i, a[i]});
    }
    for (int i = 1, op, l, r, x, y; i <= m; i++) {
        op = (rnd() % 4) + 1;
        l = (rnd() % n) + 1;
        r = (rnd() % n) + 1;
        if (l > r) swap(l, r);
        if (op == 1) {
            x = (rnd() % p) + 1;
            update(l, r, x);
        } else if (op == 2) {
            x = (rnd() % p) + 1;
            assign(l, r, x);
        } else if (op == 3) {
            x = (rnd() % (r - l + 1)) + 1;
            cout << querykth(l, r, x) << '\n';
        } else {
            x = (rnd() % p) + 1;
            y = (rnd() % p) + 1;
            cout << querysum(l, r, x, y) << '\n';
        }
    }
    return 0;
}