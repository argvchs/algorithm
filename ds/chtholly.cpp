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
auto cmp = [](node a, node b) { return a.l < b.l; };
set<node, decltype(cmp)> S(cmp);
vector<pair<i64, int>> tmp;
auto split(int x) {
    auto it = prev(S.upper_bound({x}));
    if (it->l == x) return it;
    int l = it->l, r = it->r;
    i64 val = it->val;
    S.erase(it);
    S.emplace(l, x - 1, val);
    return S.emplace(x, r, val).first;
}
void assign(int l, int r, int k) {
    auto ed = split(r + 1), st = split(l);
    S.erase(st, ed);
    S.emplace(l, r, k);
}
void update(int l, int r, int k) {
    auto ed = split(r + 1), st = split(l);
    for (auto it = st; it != ed; ++it) it->val += k;
}
int quickpow(int a, int b, int p) {
    int ret = 1;
    for (int i = b; i; i >>= 1, a = (i64)a * a % p)
        if (i & 1) ret = (i64)ret * a % p;
    return ret;
}
int querysum(int l, int r, int k, int p) {
    auto ed = split(r + 1), st = split(l);
    int ret = 0;
    for (auto it = st; it != ed; ++it)
        ret = (ret + (i64)quickpow(it->val % p, k, p) * (it->r - it->l + 1) % p) % p;
    return ret;
}
i64 querykth(int l, int r, int x) {
    auto ed = split(r + 1), st = split(l);
    tmp.clear();
    for (auto it = st; it != ed; ++it) tmp.emplace_back(it->val, it->r - it->l + 1);
    sort(tmp.begin(), tmp.end());
    for (auto [val, cnt] : tmp)
        if ((x -= cnt) <= 0) return val;
    return numeric_limits<i64>::max();
}
int rnd() {
    int ret = seed;
    seed = ((i64)seed * 7 + 13) % P;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> seed >> p;
    for (int i = 1; i <= n; i++) {
        a[i] = (rnd() % p) + 1;
        S.emplace(i, i, a[i]);
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
