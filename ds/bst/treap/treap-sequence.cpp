#include <chrono>
#include <iostream>
#include <random>
#include <utility>
using namespace std;
const int N = 1e5 + 5;
int n, m, rt, cnt;
struct node {
    int l, r, val, siz;
    bool rev;
    mt19937::result_type key;
} t[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int newnode(int x) { return t[++cnt] = {0, 0, x, 1, false, rng()}, cnt; }
void pushup(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
void push(int rt) { swap(t[rt].l, t[rt].r), t[rt].rev ^= true; }
void pushdown(int rt) {
    if (t[rt].rev) push(t[rt].l), push(t[rt].r), t[rt].rev = false;
}
void split(int rt, int x, int &l, int &r) {
    if (!rt) return void(l = r = 0);
    pushdown(rt);
    if (t[t[rt].l].siz >= x) split(t[r = rt].l, x, l, t[rt].l);
    else split(t[l = rt].r, x - t[t[rt].l].siz - 1, t[rt].r, r);
    pushup(rt);
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt | rt;
    pushdown(lt), pushdown(rt);
    if (t[lt].key < t[rt].key) return t[lt].r = merge(t[lt].r, rt), pushup(lt), lt;
    return t[rt].l = merge(lt, t[rt].l), pushup(rt), rt;
}
void reverse(int &rt, int x, int y) {
    int l, m, r;
    split(rt, x - 1, l, r), split(r, y - x + 1, m, r);
    push(m), rt = merge(merge(l, m), r);
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
    for (int i = 1; i <= n; i++) rt = merge(rt, newnode(i));
    for (int i = 1, l, r; i <= m; i++) cin >> l >> r, reverse(rt, l, r);
    output(rt);
}