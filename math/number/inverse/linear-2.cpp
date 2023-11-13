#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
using t32 = tuple<int, int, int>;
const int N = 5e6 + 5;
int n, m, p, a[N], s[N], t[N], inv[N], sum, ans;
t32 exgcd(int a, int b) {
    if (!b) return {1, 0, a};
    auto [x, y, gcd] = exgcd(b, a % b);
    return {y, x - a / b * y, gcd};
}
int inverse(int a, int p) { return (get<0>(exgcd(a, p)) + p) % p; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    s[0] = t[n + 1] = 1;
    for (int i = 1; i <= n; i++) s[i] = (i64)s[i - 1] * a[i] % p;
    for (int i = n; i >= 1; i--) t[i] = (i64)t[i + 1] * a[i] % p;
    sum = inverse(s[n], p);
    for (int i = 1; i <= n; i++) inv[i] = (i64)s[i - 1] * t[i + 1] % p * sum % p;
    for (int i = n; i >= 1; i--) ans = (i64)(ans + inv[i]) * m % p;
    cout << ans;
    return 0;
}