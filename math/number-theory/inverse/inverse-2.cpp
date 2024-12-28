#include <iostream>
using namespace std;
using i64 = long long;
const int N = 5e6 + 5;
int n, p, k, a[N], s[N], t[N], ans;
int qpow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % p)
        if (b & 1) ret = (i64)ret * a % p;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> k, s[0] = 1;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) s[i] = (i64)s[i - 1] * a[i] % p;
    t[n] = qpow(s[n], p - 2, p);
    for (int i = n; i >= 2; i--) t[i - 1] = (i64)t[i] * a[i] % p;
    for (int i = n; i >= 1; i--) ans = (ans + (i64)s[i - 1] * t[i] % p) * k % p;
    cout << ans;
}