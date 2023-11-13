#include <chrono>
#include <iostream>
#include <random>
using namespace std;
using p32 = pair<int, int>;
const int N = 5e5 + 5;
int n, rt[N], cnt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
} t[N * 75];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void maintain(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
p32 splitval(int rt, int x) {
    if (!rt) return {};
    t[++cnt] = t[rt], rt = cnt;
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
    t[++cnt] = t[rt], rt = cnt;
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
        t[++cnt] = t[lt], lt = cnt, t[lt].r = merge(t[lt].r, rt);
        return maintain(lt), lt;
    } else {
        t[++cnt] = t[rt], rt = cnt, t[rt].l = merge(lt, t[rt].l);
        return maintain(rt), rt;
    }
}
int insert(int rt, int x) {
    auto [l, r] = splitval(rt, x);
    t[++cnt] = {0, 0, x, 1, rng()};
    return merge(merge(l, cnt), r);
}
int remove(int rt, int x) {
    auto [l, _] = splitval(rt, x);
    auto [m, r] = splitval(_, x + 1);
    return merge(merge(l, splitrnk(m, 1).second), r);
}
int queryrnk(int rt, int x) {
    auto [l, r] = splitval(rt, x);
    return t[l].siz + 1;
}
int querykth(int rt, int x) {
    auto [l, _] = splitrnk(rt, x - 1);
    auto [m, r] = splitrnk(_, 1);
    return t[m].val;
}
int querypre(int rt, int x) { return querykth(rt, queryrnk(rt, x) - 1); }
int querynex(int rt, int x) { return querykth(rt, queryrnk(rt, x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, ver, op, x; i <= n; i++) {
        cin >> ver >> op >> x;
        if (op == 1) rt[i] = insert(rt[ver], x);
        else if (op == 2) rt[i] = remove(rt[ver], x);
        else if (op == 3) cout << queryrnk(rt[i] = rt[ver], x) << '\n';
        else if (op == 4) cout << querykth(rt[i] = rt[ver], x) << '\n';
        else if (op == 5) cout << querypre(rt[i] = rt[ver], x) << '\n';
        else cout << querynex(rt[i] = rt[ver], x) << '\n';
    }
    return 0;
}