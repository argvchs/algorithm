#include <iostream>
using namespace std;
using i64 = long long;
using t32 = tuple<int, int, int>;
const int N = 2e3 + 5, P = 998244353;
int n, m, a[N], b[N], ans;
int quickpow(int a, int b) {
    int ret = 1;
    for (int i = b; i; i >>= 1, a = (i64)a * a % P)
        if (i & 1) ret = (i64)ret * a % P;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        int s1 = 1, s2 = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            s1 = (i64)s1 * (m - a[j] + P) % P;
            s2 = (i64)s2 * (a[i] - a[j] + P) % P;
        }
        ans = (ans + (i64)b[i] * s1 % P * quickpow(s2, P - 2)) % P;
    }
    cout << ans;
    return 0;
}