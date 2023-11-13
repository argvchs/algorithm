#include <chrono>
#include <iostream>
#include <random>
using namespace std;
using p32 = pair<int, int>;
const int N = 1e5 + 5;
int n, rt, cnt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
} t[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void maintain(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
p32 splitval(int rt, int x) {
    if (!rt) return {};
    if (t[rt].val >= x) {
        auto [l, r] = splitval(t[rt].l, x);
        t[rt].l = r, maintain(rt);
        return {l, rt};
    } else {
        auto [l, r] = splitval(t[rt].r, x);
        t[rt].r = l, maintain(rt);
        return {rt, r};
    }
}
p32 splitrnk(int rt, int x) {
    if (!rt) return {};
    if (t[t[rt].l].siz >= x) {
        auto [l, r] = splitrnk(t[rt].l, x);
        t[rt].l = r, maintain(rt);
        return {l, rt};
    } else {
        auto [l, r] = splitrnk(t[rt].r, x - t[t[rt].l].siz - 1);
        t[rt].r = l, maintain(rt);
        return {rt, r};
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (t[lt].key < t[rt].key) {
        t[lt].r = merge(t[lt].r, rt);
        return maintain(lt), lt;
    } else {
        t[rt].l = merge(lt, t[rt].l);
        return maintain(rt), rt;
    }
}
void insert(int x) {
    auto [l, r] = splitval(rt, x);
    t[++cnt] = {0, 0, x, 1, rng()};
    rt = merge(merge(l, cnt), r);
}
void remove(int x) {
    auto [l, _] = splitval(rt, x);
    auto [m, r] = splitval(_, x + 1);
    rt = merge(merge(l, splitrnk(m, 1).second), r);
}
int queryrnk(int x) {
    auto [l, r] = splitval(rt, x);
    int ret = t[l].siz + 1;
    rt = merge(l, r);
    return ret;
}
int querykth(int x) {
    auto [l, _] = splitrnk(rt, x - 1);
    auto [m, r] = splitrnk(_, 1);
    int ret = t[m].val;
    rt = merge(merge(l, m), r);
    return ret;
}
int querypre(int x) { return querykth(queryrnk(x) - 1); }
int querynex(int x) { return querykth(queryrnk(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) insert(x);
        else if (op == 2) remove(x);
        else if (op == 3) cout << queryrnk(x) << '\n';
        else if (op == 4) cout << querykth(x) << '\n';
        else if (op == 5) cout << querypre(x) << '\n';
        else cout << querynex(x) << '\n';
    }
    return 0;
}