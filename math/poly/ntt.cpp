#include <algorithm>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 3e6 + 5, P = 998244353;
int n, m, f[N], g[N], r[N], w[N], lim = 1, cnt;
int qpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % P)
        if (b & 1) ret = (i64)ret * a % P;
    return ret;
}
void ntt(int f[], int t) {
    for (int i = 0; i < lim; i++)
        if (i < r[i]) swap(f[i], f[r[i]]);
    for (int i = 1; i < lim; i <<= 1)
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; k++) {
                int x = f[j + k], y = (i64)f[j + k + i] * w[i + k] % P;
                f[j + k] = (x + y) % P, f[j + k + i] = (x - y + P) % P;
            }
    if (t == 1) return;
    reverse(f + 1, f + lim);
    int inv = qpow(lim, P - 2);
    for (int i = 0; i < lim; i++) f[i] = (i64)f[i] * inv % P;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> f[i];
    for (int i = 0; i <= m; i++) cin >> g[i];
    while (lim <= n + m) lim <<= 1, ++cnt;
    int wn = qpow(3, (P - 1) >> cnt);
    w[lim >> 1] = 1;
    for (int i = (lim >> 1) + 1; i < lim; i++) w[i] = (i64)w[i - 1] * wn % P;
    for (int i = (lim >> 1) - 1; i > 0; i--) w[i] = w[i << 1];
    for (int i = 0; i < lim; i++) r[i] = r[i >> 1] >> 1 | (i & 1) << (cnt - 1);
    ntt(f, 1), ntt(g, 1);
    for (int i = 0; i < lim; i++) f[i] = (i64)f[i] * g[i] % P;
    ntt(f, -1);
    for (int i = 0; i <= n + m; i++) cout << f[i] << ' ';
}