#include <algorithm>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, a[N];
struct node {
    i64 sum, add;
} t[N << 2];
void bulid(int rt, int l, int r) {
    if (l == r) return void(t[rt].sum = a[l]);
    int mid = (l + r) >> 1;
    bulid(rt << 1, l, mid);
    bulid(rt << 1 | 1, mid + 1, r);
    t[rt].sum = t[rt << 1].sum + t[rt << 1 | 1].sum;
}
void update(int rt, int l, int r, int x, int y, int k) {
    t[rt].sum += (min(r, y) - max(l, x) + 1) * k;
    if (x <= l && r <= y) return void(t[rt].add += k);
    int mid = (l + r) >> 1;
    if (x <= mid) update(rt << 1, l, mid, x, y, k);
    if (y >= mid + 1) update(rt << 1 | 1, mid + 1, r, x, y, k);
}
i64 query(int rt, int l, int r, int x, int y) {
    if (x <= l && r <= y) return t[rt].sum;
    int mid = (l + r) >> 1;
    i64 ret = (min(r, y) - max(l, x) + 1) * t[rt].add;
    if (x <= mid) ret += query(rt << 1, l, mid, x, y);
    if (y >= mid + 1) ret += query(rt << 1 | 1, mid + 1, r, x, y);
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    bulid(1, 1, n);
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) cin >> k, update(1, 1, n, l, r, k);
        else cout << query(1, 1, n, l, r) << '\n';
    }
}