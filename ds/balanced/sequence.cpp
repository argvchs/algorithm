#include <chrono>
#include <iostream>
#include <random>
#include <stack>
using namespace std;
using p32 = pair<int, int>;
const int N = 1e5 + 5;
int n, m, rt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
    bool rev;
} t[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
stack<int> S;
void pushup(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
void pushdown(int rt) {
    if (!t[rt].rev) return;
    swap(t[rt].l, t[rt].r);
    t[t[rt].l].rev ^= 1, t[t[rt].r].rev ^= 1;
    t[rt].rev = false;
}
p32 split(int rt, int x) {
    if (!rt) return {};
    pushdown(rt);
    if (t[t[rt].l].siz >= x) {
        auto [l, r] = split(t[rt].l, x);
        t[rt].l = r, pushup(rt);
        return {l, rt};
    } else {
        auto [l, r] = split(t[rt].r, x - t[t[rt].l].siz - 1);
        t[rt].r = l, pushup(rt);
        return {rt, r};
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    pushdown(lt), pushdown(rt);
    if (t[lt].key < t[rt].key) {
        t[lt].r = merge(t[lt].r, rt);
        return pushup(lt), lt;
    } else {
        t[rt].l = merge(lt, t[rt].l);
        return pushup(rt), rt;
    }
}
void reverse(int x, int y) {
    auto [l, _] = split(rt, x - 1);
    auto [m, r] = split(_, y - x + 1);
    t[m].rev ^= 1;
    rt = merge(merge(l, m), r);
}
void output(int rt) {
    if (!rt) return;
    pushdown(rt);
    output(t[rt].l);
    cout << t[rt].val << ' ';
    output(t[rt].r);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) t[i] = {0, 0, i, 1, rng()};
    for (int i = 1; i <= n; i++) rt = merge(rt, i);
    for (int i = 1, l, r; i <= m; i++) cin >> l >> r, reverse(l, r);
    output(rt);
    return 0;
}