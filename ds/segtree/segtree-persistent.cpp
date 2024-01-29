#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], rt[N], cnt;
struct node {
    int l, r, val;
} t[N << 5];
void build(int &rt, int l, int r) {
    rt = ++cnt;
    if (l == r) return void(t[rt].val = a[l]);
    int mid = (l + r) >> 1;
    build(t[rt].l, l, mid);
    build(t[rt].r, mid + 1, r);
}
void update(int &rt, int l, int r, int x, int k) {
    t[++cnt] = t[rt], rt = cnt;
    if (l == r) return void(t[rt].val = k);
    int mid = (l + r) >> 1;
    if (x <= mid) update(t[rt].l, l, mid, x, k);
    else update(t[rt].r, mid + 1, r, x, k);
}
int query(int rt, int l, int r, int x) {
    if (l == r) return t[rt].val;
    int mid = (l + r) >> 1;
    if (x <= mid) return query(t[rt].l, l, mid, x);
    return query(t[rt].r, mid + 1, r, x);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(rt[0], 1, n);
    for (int i = 1, v, op, x, k; i <= m; i++) {
        cin >> v >> op >> x, rt[i] = rt[v];
        if (op == 1) cin >> k, update(rt[i], 1, n, x, k);
        else cout << query(rt[i], 1, n, x) << '\n';
    }
    return 0;
}