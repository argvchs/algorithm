#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, p, t, f[N], g[N];
int lucas(int n, int m, int p) {
    if (!m) return 1;
    if (n < m) return 0;
    if (n < p) return (i64)f[n] * g[f[m]] * g[f[n - m]] % p;
    return (i64)lucas(n / p, m / p, p) * lucas(n % p, m % p, p) % p;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> m >> p;
        f[0] = f[1] = g[1] = 1;
        for (int i = 2; i <= p; i++) f[i] = (i64)f[i - 1] * i % p;
        for (int i = 2; i <= p; i++) g[i] = (i64)(p - p / i) * g[p % i] % p;
        cout << lucas(n + m, n, p) << '\n';
    }
    return 0;
}