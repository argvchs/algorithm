#include <iostream>
using namespace std;
using i64 = long long;
const int N = 5e6 + 5;
int n, m, p, a[N], s[N], t[N], inv[N], ans;
int quickpow(int a, int b, int p) {
    int ret = 1;
    for (int i = b; i; i >>= 1, a = (i64)a * a % p)
        if (i & 1) ret = (i64)ret * a % p;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    s[0] = t[n + 1] = 1;
    for (int i = 1; i <= n; i++) s[i] = (i64)s[i - 1] * a[i] % p;
    for (int i = n; i >= 1; i--) t[i] = (i64)t[i + 1] * a[i] % p;
    int k = quickpow(s[n], p - 2, p);
    for (int i = 1; i <= n; i++) inv[i] = (i64)s[i - 1] * t[i + 1] % p * k % p;
    for (int i = n; i >= 1; i--) ans = (i64)(ans + inv[i]) * m % p;
    cout << ans;
    return 0;
}