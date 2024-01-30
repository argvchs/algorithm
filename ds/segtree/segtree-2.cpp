#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5, P = 571373;
int n, m, p, a[N];
struct node {
    int sum, add, mul = 1;
} t[N << 2];
void pushup(int rt) { t[rt].sum = (t[rt << 1].sum + t[rt << 1 | 1].sum) % P; }
void push(int rt, int l, int r, int x, int y) {
    t[rt].sum = ((i64)t[rt].sum * x + y * (i64)(r - l + 1)) % P;
    t[rt].add = ((i64)t[rt].add * x + y) % P;
    t[rt].mul = (i64)t[rt].mul * x % P;
}
void pushdown(int rt, int l, int r) {
    int mid = (l + r) >> 1;
    push(rt << 1, l, mid, t[rt].mul, t[rt].add);
    push(rt << 1 | 1, mid + 1, r, t[rt].mul, t[rt].add);
    t[rt].add = 0, t[rt].mul = 1;
}
void build(int rt, int l, int r) {
    if (l == r) return void(t[rt].sum = a[l] % P);
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    pushup(rt);
}
void updateadd(int rt, int l, int r, int x, int y, int k) {
    if (x <= l && r <= y) return push(rt, l, r, 1, k);
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid) updateadd(rt << 1, l, mid, x, y, k);
    if (y >= mid + 1) updateadd(rt << 1 | 1, mid + 1, r, x, y, k);
    pushup(rt);
}
void updatemul(int rt, int l, int r, int x, int y, int k) {
    if (x <= l && r <= y) return push(rt, l, r, k, 0);
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if (x <= mid) updatemul(rt << 1, l, mid, x, y, k);
    if (y >= mid + 1) updatemul(rt << 1 | 1, mid + 1, r, x, y, k);
    pushup(rt);
}
int query(int rt, int l, int r, int x, int y) {
    if (x <= l && r <= y) return t[rt].sum;
    pushdown(rt, l, r);
    int mid = (l + r) >> 1, ret = 0;
    if (x <= mid) ret = (ret + query(rt << 1, l, mid, x, y)) % P;
    if (y >= mid + 1) ret = (ret + query(rt << 1 | 1, mid + 1, r, x, y)) % P;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) cin >> k, updatemul(1, 1, n, l, r, k);
        else if (op == 2) cin >> k, updateadd(1, 1, n, l, r, k);
        else cout << query(1, 1, n, l, r) << '\n';
    }
}