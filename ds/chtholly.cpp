#include <algorithm>
#include <iostream>
#include <set>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;
const int P = 1e9 + 7;
int n, m, s, v;
struct node {
    int l, r;
    mutable i64 val;
    bool operator<(const node &x) const { return l < x.l; }
};
set<node> S;
vector<pair<i64, i64>> tmp;
auto split(int x) {
    auto it = --S.upper_bound({x, 0, 0});
    if (it->l == x) return it;
    auto [l, r, val] = *it;
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
int qpow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % p)
        if (b & 1) ret = (i64)ret * a % p;
    return ret;
}
int querysum(int l, int r, int k, int p) {
    auto ed = split(r + 1), st = split(l);
    int ret = 0;
    for (auto it = st; it != ed; ++it)
        (ret += (i64)qpow(it->val % p, k, p) * (it->r - it->l + 1) % p) %= p;
    return ret;
}
i64 querykth(int l, int r, int k) {
    auto ed = split(r + 1), st = split(l);
    tmp.clear();
    for (auto it = st; it != ed; ++it) tmp.emplace_back(it->val, it->r - it->l + 1);
    sort(tmp.begin(), tmp.end());
    for (auto [x, y] : tmp)
        if ((k -= y) <= 0) return x;
    return -1;
}
int gen(int x) { return exchange(s, ((i64)s * 7 + 13) % P) % x + 1; }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> v;
    for (int i = 1; i <= n; i++) S.emplace(i, i, gen(v));
    for (int i = 1, op, l, r, x; i <= m; i++) {
        op = gen(4), l = gen(n), r = gen(n);
        if (l > r) swap(l, r);
        if (op == 1) update(l, r, gen(v));
        else if (op == 2) assign(l, r, gen(v));
        else if (op == 3) cout << querykth(l, r, gen(r - l + 1)) << '\n';
        else x = gen(v), cout << querysum(l, r, x, gen(v)) << '\n';
    }
}