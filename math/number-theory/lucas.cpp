#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int T, n, m, p, fac[N], inv[N];
int lucas(int n, int m, int p) {
    if (!m) return 1;
    if (n < m) return 0;
    if (n < p) return (i64)fac[n] * inv[fac[m]] * inv[fac[n - m]] % p;
    return (i64)lucas(n / p, m / p, p) * lucas(n % p, m % p, p) % p;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> n >> m >> p;
        fac[0] = fac[1] = inv[1] = 1;
        for (int i = 2; i <= p; i++) fac[i] = (i64)fac[i - 1] * i % p;
        for (int i = 2; i <= p; i++) inv[i] = (i64)(p - p / i) * inv[p % i] % p;
        cout << lucas(n + m, n, p) << '\n';
    }
}