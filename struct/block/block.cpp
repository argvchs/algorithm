#include <cmath>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5, P = 571373;
int n, m, k, a[N], belong[N], sum[N], add[N], mul[N], siz, tot;
void spread(int x) {
    for (int i = (x - 1) * siz + 1; i <= min(x * siz, n); i++)
        a[i] = ((i64)a[i] * mul[x] + add[x]) % P;
    add[x] = 0, mul[x] = 1;
}
void maintain(int x) {
    sum[x] = 0;
    for (int i = (x - 1) * siz + 1; i <= min(x * siz, n); i++) sum[x] = (sum[x] + a[i]) % P;
}
void build() {
    siz = sqrt(n), tot = (n - 1) / siz + 1;
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= tot; i++) mul[i] = 1, maintain(i);
}
void updatemul(int l, int r, int k) {
    int x = belong[l], y = belong[r];
    spread(x), spread(y);
    if (x == y) {
        for (int i = l; i <= r; i++) a[i] = (i64)a[i] * k % P;
        maintain(x);
        return;
    }
    for (int i = l; belong[i] == x; i++) a[i] = (i64)a[i] * k % P;
    for (int i = r; belong[i] == y; i--) a[i] = (i64)a[i] * k % P;
    maintain(x), maintain(y);
    for (int i = x + 1; i <= y - 1; i++) {
        sum[i] = (i64)sum[i] * k % P;
        add[i] = (i64)add[i] * k % P;
        mul[i] = (i64)mul[i] * k % P;
    }
}
void updateadd(int l, int r, int k) {
    int x = belong[l], y = belong[r];
    spread(x), spread(y);
    if (x == y) {
        for (int i = l; i <= r; i++) a[i] = (a[i] + k) % P;
        maintain(x);
        return;
    }
    for (int i = l; belong[i] == x; i++) a[i] = (a[i] + k) % P;
    for (int i = r; belong[i] == y; i--) a[i] = (a[i] + k) % P;
    maintain(x), maintain(y);
    for (int i = x + 1; i <= y - 1; i++) {
        sum[i] = (sum[i] + (i64)siz * k) % P;
        add[i] = (add[i] + k) % P;
    }
}
int query(int l, int r) {
    int x = belong[l], y = belong[r], res = 0;
    spread(x), spread(y);
    if (x == y) {
        for (int i = l; i <= r; i++) res = (res + a[i]) % P;
        return res;
    }
    for (int i = l; belong[i] == x; i++) res = (res + a[i]) % P;
    for (int i = r; belong[i] == y; i--) res = (res + a[i]) % P;
    maintain(x), maintain(y);
    for (int i = x + 1; i <= y - 1; i++) res = (res + sum[i]) % P;
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    for (int i = 1, op, l, r, k; i <= m; i++) {
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> k;
            updatemul(l, r, k);
        } else if (op == 2) {
            cin >> k;
            updateadd(l, r, k);
        } else cout << query(l, r) << '\n';
    }
    return 0;
}