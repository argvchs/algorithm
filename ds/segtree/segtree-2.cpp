#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, p, a[N];
struct node {
    int l, r, val, add, mul;
} t[N << 2];
void pushup(int rt) { t[rt].val = (t[rt << 1].val + t[rt << 1 | 1].val) % p; }
void pushdown(int rt) {
    int l = rt << 1, r = rt << 1 | 1;
    t[l].val = ((i64)t[l].val * t[rt].mul + (i64)(t[l].r - t[l].l + 1) * t[rt].add) % p;
    t[l].add = ((i64)t[l].add * t[rt].mul % p + t[rt].add) % p;
    t[l].mul = (i64)t[l].mul * t[rt].mul % p;
    t[r].val = ((i64)t[r].val * t[rt].mul + (i64)(t[r].r - t[r].l + 1) * t[rt].add) % p;
    t[r].add = ((i64)t[r].add * t[rt].mul % p + t[rt].add) % p;
    t[r].mul = (i64)t[r].mul * t[rt].mul % p;
    t[rt].add = 0, t[rt].mul = 1;
}
void build(int rt, int l, int r) {
    t[rt].l = l, t[rt].r = r, t[rt].mul = 1;
    if (l == r) return void(t[rt].val = a[l] % p);
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}
void updateadd(int rt, int l, int r, int k) {
    if (r < t[rt].l || t[rt].r < l) return;
    if (l <= t[rt].l && t[rt].r <= r) {
        t[rt].val = (t[rt].val + (i64)(t[rt].r - t[rt].l + 1) * k) % p;
        t[rt].add = (t[rt].add + k) % p;
        return;
    }
    pushdown(rt);
    updateadd(rt << 1, l, r, k);
    updateadd(rt << 1 | 1, l, r, k);
    pushup(rt);
}
void updatemul(int rt, int l, int r, int k) {
    if (r < t[rt].l || t[rt].r < l) return;
    if (l <= t[rt].l && t[rt].r <= r) {
        t[rt].val = (i64)t[rt].val * k % p;
        t[rt].mul = (i64)t[rt].mul * k % p;
        t[rt].add = (i64)t[rt].add * k % p;
        return;
    }
    pushdown(rt);
    updatemul(rt << 1, l, r, k);
    updatemul(rt << 1 | 1, l, r, k);
    pushup(rt);
}
int query(int rt, int l, int r) {
    if (r < t[rt].l || t[rt].r < l) return 0;
    if (l <= t[rt].l && t[rt].r <= r) return t[rt].val;
    pushdown(rt);
    return (query(rt << 1, l, r) + query(rt << 1 | 1, l, r)) % p;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) cin >> k, updatemul(1, l, r, k);
        else if (op == 2) cin >> k, updateadd(1, l, r, k);
        else cout << query(1, l, r) << '\n';
    }
    return 0;
}