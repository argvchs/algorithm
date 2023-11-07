#include <cmath>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5, P = 571373;
int n, m, k, a[N], bel[N], st[N], ed[N], sum[N], add[N], mul[N], siz, tot;
void spread(int x) {
    for (int i = st[x]; i <= ed[x]; i++) a[i] = ((i64)a[i] * mul[x] + add[x]) % P;
    add[x] = 0, mul[x] = 1;
}
void maintain(int x) {
    sum[x] = 0;
    for (int i = st[x]; i <= ed[x]; i++) sum[x] = (sum[x] + a[i]) % P;
}
void build() {
    siz = sqrt(n), tot = (n - 1) / siz + 1;
    for (int i = 1; i <= n; i++) bel[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= tot; i++) st[i] = (i - 1) * siz + 1, ed[i] = min(i * siz, n);
    for (int i = 1; i <= tot; i++) mul[i] = 1, maintain(i);
}
void updatemul(int l, int r, int k) {
    spread(bel[l]), spread(bel[r]);
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) a[i] = (i64)a[i] * k % P;
        return maintain(bel[l]);
    }
    for (int i = l; bel[i] == bel[l]; i++) a[i] = (i64)a[i] * k % P;
    for (int i = r; bel[i] == bel[r]; i--) a[i] = (i64)a[i] * k % P;
    maintain(bel[l]), maintain(bel[r]);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
        sum[i] = (i64)sum[i] * k % P;
        add[i] = (i64)add[i] * k % P;
        mul[i] = (i64)mul[i] * k % P;
    }
}
void updateadd(int l, int r, int k) {
    spread(bel[l]), spread(bel[r]);
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) a[i] = (a[i] + k) % P;
        return maintain(bel[l]);
    }
    for (int i = l; bel[i] == bel[l]; i++) a[i] = (a[i] + k) % P;
    for (int i = r; bel[i] == bel[r]; i--) a[i] = (a[i] + k) % P;
    maintain(bel[l]), maintain(bel[r]);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) {
        sum[i] = (sum[i] + (i64)siz * k) % P;
        add[i] = (add[i] + k) % P;
    }
}
int query(int l, int r) {
    int ret = 0;
    spread(bel[l]), spread(bel[r]);
    if (bel[l] == bel[r]) {
        for (int i = l; i <= r; i++) ret = (ret + a[i]) % P;
        return ret;
    }
    for (int i = l; bel[i] == bel[l]; i++) ret = (ret + a[i]) % P;
    for (int i = r; bel[i] == bel[r]; i--) ret = (ret + a[i]) % P;
    maintain(bel[l]), maintain(bel[r]);
    for (int i = bel[l] + 1; i <= bel[r] - 1; i++) ret = (ret + sum[i]) % P;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) cin >> k, updatemul(l, r, k);
        else if (op == 2) cin >> k, updateadd(l, r, k);
        else cout << query(l, r) << '\n';
    }
    return 0;
}