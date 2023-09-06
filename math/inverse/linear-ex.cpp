#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 5e6 + 5;
int n, p, k, a[N], s[N], t[N], inv[N], sum, ans;
tuple<int, int, int> exgcd(int a, int b) {
    if (!b) return {1, 0, a};
    auto [x, y, gcd] = exgcd(b, a % b);
    return {y, x - a / b * y, gcd};
}
int inverse(int a, int p) { return (get<0>(exgcd(a, p)) + p) % p; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    s[0] = t[n + 1] = 1;
    for (int i = 1; i <= n; i++) s[i] = (i64)s[i - 1] * a[i] % p;
    for (int i = n; i >= 1; i--) t[i] = (i64)t[i + 1] * a[i] % p;
    sum = inverse(s[n], p);
    for (int i = 1; i <= n; i++) inv[i] = (i64)s[i - 1] * t[i + 1] % p * sum % p;
    for (int i = n; i >= 1; i--) ans = (i64)(ans + inv[i]) * k % p;
    cout << ans;
    return 0;
}