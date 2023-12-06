#include <iostream>
using namespace std;
using i64 = long long;
const int N = 3e6 + 5, P = 998244353;
int n, m, a[N], b[N], r[N], lim = 1, cnt;
int qpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % P)
        if (b & 1) ret = (i64)ret * a % P;
    return ret;
}
void ntt(int a[], int t) {
    for (int i = 0; i < lim; i++)
        if (i < r[i]) swap(a[i], a[r[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        int wn = qpow(t == 1 ? 3 : 332748118, (P - 1) / (i << 1));
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0, w = 1; k < i; k++, w = (i64)w * wn % P) {
                int x = a[j + k], y = (i64)a[j + k + i] * w % P;
                a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
            }
    }
    if (t == 1) return;
    int inv = qpow(lim, P - 2);
    for (int i = 0; i < lim; i++) a[i] = (i64)a[i] * inv % P;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];
    while (lim <= n + m) lim <<= 1, ++cnt;
    for (int i = 0; i < lim; i++) r[i] = r[i >> 1] >> 1 | (i & 1) << (cnt - 1);
    ntt(a, 1), ntt(b, 1);
    for (int i = 0; i < lim; i++) a[i] = (i64)a[i] * b[i] % P;
    ntt(a, -1);
    for (int i = 0; i <= n + m; i++) cout << a[i] << ' ';
    return 0;
}