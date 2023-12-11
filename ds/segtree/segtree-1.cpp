#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, a[N];
struct node {
    int l, r;
    i64 sum, add;
} t[N << 2];
void pushup(int rt) { t[rt].sum = t[rt << 1].sum + t[rt << 1 | 1].sum; }
void pushdown(int rt) {
    int l = rt << 1, r = rt << 1 | 1;
    t[l].sum += (t[l].r - t[l].l + 1) * t[rt].add;
    t[l].add += t[rt].add;
    t[r].sum += (t[r].r - t[r].l + 1) * t[rt].add;
    t[r].add += t[rt].add;
    t[rt].add = 0;
}
void bulid(int rt, int l, int r) {
    t[rt].l = l, t[rt].r = r;
    if (l == r) return void(t[rt].sum = a[l]);
    int mid = (l + r) >> 1;
    bulid(rt << 1, l, mid);
    bulid(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}
void update(int rt, int l, int r, int k) {
    if (r < t[rt].l || t[rt].r < l) return;
    if (l <= t[rt].l && t[rt].r <= r) {
        t[rt].sum += (t[rt].r - t[rt].l + 1) * k;
        t[rt].add += k;
        return;
    }
    pushdown(rt);
    update(rt << 1, l, r, k);
    update(rt << 1 | 1, l, r, k);
    pushup(rt);
}
i64 query(int rt, int l, int r) {
    if (r < t[rt].l || t[rt].r < l) return 0;
    if (l <= t[rt].l && t[rt].r <= r) return t[rt].sum;
    pushdown(rt);
    return query(rt << 1, l, r) + query(rt << 1 | 1, l, r);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    bulid(1, 1, n);
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) cin >> k, update(1, l, r, k);
        else cout << query(1, l, r) << '\n';
    }
    return 0;
}