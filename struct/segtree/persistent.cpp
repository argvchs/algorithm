#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], rt[N], cnt;
struct node {
    int l, r, val;
} t[N * 25];
int build(int l, int r) {
    int cur = ++cnt;
    if (l == r) return t[cur].val = a[l], cur;
    int mid = (l + r) >> 1;
    t[cur].l = build(l, mid);
    t[cur].r = build(mid + 1, r);
    return cur;
}
int update(int rt, int l, int r, int x, int k) {
    if (x < l || r < x) return rt;
    int cur = ++cnt;
    if (l == r) return t[cur].val = k, cur;
    int mid = (l + r) >> 1;
    t[cur].l = update(t[rt].l, l, mid, x, k);
    t[cur].r = update(t[rt].r, mid + 1, r, x, k);
    return cur;
}
int query(int rt, int l, int r, int x) {
    if (x < l || r < x) return 0;
    if (l == r) return t[rt].val;
    int mid = (l + r) >> 1;
    return query(t[rt].l, l, mid, x) + query(t[rt].r, mid + 1, r, x);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    rt[0] = build(1, n);
    for (int i = 1, ver, op, x, k; i <= m; i++) {
        cin >> ver >> op >> x;
        if (op == 1) cin >> k, rt[i] = update(rt[ver], 1, n, x, k);
        else cout << query(rt[i] = rt[ver], 1, n, x) << '\n';
    }
    return 0;
}