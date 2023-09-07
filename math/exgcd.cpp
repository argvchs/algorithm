#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
int a, b, c, t;
auto exgcd(int a, int b) {
    if (!b) return make_tuple(1ll, 0ll, a);
    auto [x, y, gcd] = exgcd(b, a % b);
    return make_tuple(y, x - a / b * y, gcd);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        auto [x, y, gcd] = exgcd(a, b);
        if (c % gcd) {
            cout << "-1\n";
            continue;
        }
        a /= gcd, b /= gcd, c /= gcd, x *= c, y *= c;
        i64 xmin = (x % b + b - 1) % b + 1;
        i64 ymin = (y % a + a - 1) % a + 1;
        i64 xmax = (c - ymin * b) / a;
        i64 ymax = (c - xmin * a) / b;
        if (xmax > 0) {
            int cnt = (xmax - xmin) / b + 1;
            cout << cnt << ' ' << xmin << ' ' << ymin << ' ' << xmax << ' ' << ymax << '\n';
        } else cout << xmin << ' ' << ymin << '\n';
    }
    return 0;
}