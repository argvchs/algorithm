#include <iostream>
using namespace std;
using i64 = long long;
const int N = 3e6 + 5, P = 998244353, G = 3, I = 332748118;
int n, m, r[N], lim = 1, cnt;
i64 f[N], g[N];
i64 quickpow(i64 a, i64 b) {
    i64 ret = 1;
    for (i64 i = b; i; i >>= 1, a = a * a % P)
        if (i & 1) ret = ret * a % P;
    return ret;
}
void ntt(i64 a[], int t) {
    for (int i = 0; i < lim; i++)
        if (i < r[i]) swap(a[i], a[r[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        i64 rt = quickpow(t == 1 ? G : I, (P - 1) / (i << 1));
        for (int j = 0; j < lim; j += i << 1) {
            i64 w = 1;
            for (int k = 0; k < i; k++, w = w * rt % P) {
                i64 x = a[j + k], y = a[j + k + i] * w % P;
                a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> f[i];
    for (int i = 0; i <= m; i++) cin >> g[i];
    while (lim <= n + m) lim <<= 1, ++cnt;
    for (int i = 0; i < lim; i++) r[i] = r[i >> 1] >> 1 | (i & 1) << (cnt - 1);
    ntt(f, 1), ntt(g, 1);
    for (int i = 0; i < lim; i++) f[i] = f[i] * g[i] % P;
    ntt(f, -1);
    int inv = quickpow(lim, P - 2);
    for (int i = 0; i <= n + m; i++) cout << f[i] * inv % P << ' ';
    return 0;
}