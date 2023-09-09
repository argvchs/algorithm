#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 2e3 + 5, P = 998244353;
int n, m, a[N], b[N], sum1, sum2, ans;
tuple<int, int, int> exgcd(int a, int b) {
    if (!b) return {1, 0, a};
    auto [x, y, gcd] = exgcd(b, a % b);
    return {y, x - (a / b) * y, gcd};
}
int inverse(int a) { return (get<0>(exgcd(a, P)) + P) % P; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; i++) {
        sum1 = sum2 = 1;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            sum1 = (i64)sum1 * (m - a[j] + P) % P;
            sum2 = (i64)sum2 * (a[i] - a[j] + P) % P;
        }
        ans = (ans + (i64)b[i] * sum1 % P * inverse(sum2)) % P;
    }
    cout << ans;
    return 0;
}