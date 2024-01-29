#include <chrono>
#include <iostream>
#include <random>
using namespace std;
const int N = 1e5 + 5;
int n, m, rt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
    bool rev;
} t[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void pushup(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
void pushdown(int rt) {
    if (!t[rt].rev) return;
    swap(t[rt].l, t[rt].r);
    t[t[rt].l].rev ^= true, t[t[rt].r].rev ^= true;
    t[rt].rev = false;
}
void split(int rt, int x, int &l, int &r) {
    if (!rt) return void(l = r = 0);
    if (t[t[rt].l].siz >= x) r = rt, split(t[rt].l, x, l, t[rt].l);
    else l = rt, split(t[rt].r, x - t[t[rt].l].siz - 1, t[rt].r, r);
    pushup(rt);
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    pushdown(lt), pushdown(rt);
    if (t[lt].key < t[rt].key) t[lt].r = merge(t[lt].r, rt), rt = lt;
    else t[rt].l = merge(lt, t[rt].l);
    return pushup(rt), rt;
}
void reverse(int &rt, int x, int y) {
    int l, m, r;
    split(rt, x - 1, l, m), split(m, y - x + 1, m, r);
    t[m].rev ^= true;
    rt = merge(merge(l, m), r);
}
void output(int rt) {
    if (!rt) return;
    pushdown(rt);
    output(t[rt].l), cout << t[rt].val << ' ', output(t[rt].r);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) t[i] = {0, 0, i, 1, rng()};
    for (int i = 1; i <= n; i++) rt = merge(rt, i);
    for (int i = 1, l, r; i <= m; i++) cin >> l >> r, reverse(rt, l, r);
    output(rt);
}