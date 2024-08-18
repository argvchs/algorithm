#include <iostream>
using namespace std;
using i64 = long long;
const int N = 2e3 + 5, P = 998244353;
int n, m, a[N], b[N], ans;
int qpow(int a, int b) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % P)
        if (b & 1) ret = (i64)ret * a % P;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        int x = 1, y = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            x = (i64)x * (m - a[j] + P) % P;
            y = (i64)y * (a[i] - a[j] + P) % P;
        }
        ans = (ans + (i64)b[i] * x % P * qpow(y, P - 2)) % P;
    }
    cout << ans;
}