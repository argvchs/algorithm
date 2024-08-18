#include <algorithm>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 3e6 + 5, P = 998244353;
int n, m, a[N], b[N], w[N], lim = 1;
int qpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % P)
        if (b & 1) ret = (i64)ret * a % P;
    return ret;
}
void dit(int *a, int n) {
    for (int i = 1; i < n; i <<= 1)
        for (int j = 0; j < n; j += i << 1)
            for (int k = 0; k < i; k++) {
                int x = a[j + k], y = (i64)a[j + k + i] * w[i + k] % P;
                a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
            }
    int inv = qpow(n, P - 2);
    reverse(a + 1, a + n);
    for (int i = 0; i < n; i++) a[i] = (i64)a[i] * inv % P;
}
void dif(int *a, int n) {
    for (int i = n >> 1; i; i >>= 1)
        for (int j = 0; j < n; j += i << 1)
            for (int k = 0; k < i; k++) {
                int x = a[j + k], y = a[j + k + i];
                a[j + k] = (x + y) % P, a[j + k + i] = (i64)(x - y + P) * w[i + k] % P;
            }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];
    while (lim <= n + m) lim <<= 1;
    int wn = qpow(3, (P - 1) / lim);
    w[lim >> 1] = 1;
    for (int i = (lim >> 1) + 1; i < lim; i++) w[i] = (i64)w[i - 1] * wn % P;
    for (int i = (lim >> 1) - 1; i; i--) w[i] = w[i << 1];
    dif(a, lim), dif(b, lim);
    for (int i = 0; i < lim; i++) a[i] = (i64)a[i] * b[i] % P;
    dit(a, lim);
    for (int i = 0; i <= n + m; i++) cout << a[i] << ' ';
}