#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int T, n, m, p, fac[N], inv[N];
int qpow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % p)
        if (b & 1) ret = (i64)ret * a % p;
    return ret;
}
int lucas(int n, int m, int p) {
    if (n < m) return 0;
    if (n < p) return (i64)fac[n] * inv[m] * inv[n - m] % p;
    return (i64)lucas(n / p, m / p, p) * lucas(n % p, m % p, p) % p;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m >> p, fac[0] = 1;
        for (int i = 1; i <= p - 1; i++) fac[i] = (i64)fac[i - 1] * i % p;
        inv[p - 1] = qpow(p - 1, p - 2, p);
        for (int i = p - 1; i >= 1; i--) inv[i - 1] = (i64)inv[i] * i % p;
        cout << lucas(n + m, n, p) << '\n';
    }
}