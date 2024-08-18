#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5, P = 571373;
int n, m, p, a[N], bel[N], sum[N], add[N], mul[N], siz;
void pushup(int x) {
    sum[x] = 0;
    for (int i = (x - 1) * siz + 1; i <= min(x * siz, n); i++) sum[x] = (sum[x] + a[i]) % P;
}
void pushdown(int x) {
    for (int i = (x - 1) * siz + 1; i <= min(x * siz, n); i++)
        a[i] = ((i64)a[i] * mul[x] + add[x]) % P;
    add[x] = 0, mul[x] = 1;
}
void updatemul(int l, int r, int k) {
    pushdown(bel[l]), pushdown(bel[r]);
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) a[i] = (i64)a[i] * k % P;
        return pushup(bel[l]);
    }
    for (int i = l; bel[i] == bel[l]; i++) a[i] = (i64)a[i] * k % P;
    for (int i = r; bel[i] == bel[r]; i--) a[i] = (i64)a[i] * k % P;
    pushup(bel[l]), pushup(bel[r]);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
        sum[i] = (i64)sum[i] * k % P;
        add[i] = (i64)add[i] * k % P;
        mul[i] = (i64)mul[i] * k % P;
    }
}
void updateadd(int l, int r, int k) {
    pushdown(bel[l]), pushdown(bel[r]);
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) a[i] = (a[i] + k) % P;
        return pushup(bel[l]);
    }
    for (int i = l; bel[i] == bel[l]; i++) a[i] = (a[i] + k) % P;
    for (int i = r; bel[i] == bel[r]; i--) a[i] = (a[i] + k) % P;
    pushup(bel[l]), pushup(bel[r]);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
        sum[i] = (sum[i] + (i64)siz * k) % P;
        add[i] = (add[i] + k) % P;
    }
}
int query(int l, int r) {
    pushdown(bel[l]), pushdown(bel[r]);
    int ret = 0;
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) ret = (ret + a[i]) % P;
        return ret;
    }
    for (int i = l; bel[i] == bel[l]; i++) ret = (ret + a[i]) % P;
    for (int i = r; bel[i] == bel[r]; i--) ret = (ret + a[i]) % P;
    pushup(bel[l]), pushup(bel[r]);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) ret = (ret + sum[i]) % P;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> p, siz = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i], bel[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= bel[n]; i++) mul[i] = 1, pushup(i);
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) cin >> k, updatemul(l, r, k);
        else if (op == 2) cin >> k, updateadd(l, r, k);
        else cout << query(l, r) << '\n';
    }
}