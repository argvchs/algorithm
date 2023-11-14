#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;
using p64 = pair<i64, i64>;
const int P = 1e9 + 7;
int n, m, s, p;
struct node {
    int l, r;
    mutable i64 val;
};
bool cmp(node a, node b) { return a.l < b.l; }
set<node, decltype(&cmp)> S(cmp);
vector<p64> tmp;
auto split(int x) {
    auto it = prev(S.upper_bound({x}));
    if (it->l == x) return it;
    int l = it->l, r = it->r;
    i64 val = it->val;
    S.erase(it), S.emplace(l, x - 1, val);
    return S.emplace(x, r, val).first;
}
void assign(int l, int r, int k) {
    auto ed = split(r + 1), st = split(l);
    S.erase(st, ed), S.emplace(l, r, k);
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
int gen(int x) {
    int ret = s;
    s = ((i64)s * 7 + 13) % P;
    return (ret % x) + 1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> p;
    for (int i = 1; i <= n; i++) S.emplace(i, i, gen(p));
    for (int i = 1, op, l, r, x; i <= m; i++) {
        op = gen(4), l = gen(n), r = gen(n);
        if (l > r) swap(l, r);
        if (op == 1) update(l, r, gen(p));
        else if (op == 2) assign(l, r, gen(p));
        else if (op == 3) cout << querykth(l, r, gen(r - l + 1)) << '\n';
        else x = gen(p), cout << querysum(l, r, x, gen(p)) << '\n';
    }
    return 0;
}