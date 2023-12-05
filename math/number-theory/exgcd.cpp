#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
using t64 = tuple<i64, i64, i64>;
int a, b, c, t;
t64 exgcd(int a, int b) {
    if (!b) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> a >> b >> c;
        auto [x, y, g] = exgcd(a, b);
        if (c % g) {
            cout << "-1\n";
            continue;
        }
        a /= g, b /= g, c /= g, x *= c, y *= c;
        i64 xmin = (x % b + b - 1) % b + 1;
        i64 ymin = (y % a + a - 1) % a + 1;
        i64 xmax = (c - ymin * b) / a;
        i64 ymax = (c - xmin * a) / b;
        if (xmax > 0) {
            int cnt = (xmax - xmin) / b + 1;
            cout << cnt << ' ';
            cout << xmin << ' ' << ymin << ' ';
            cout << xmax << ' ' << ymax << '\n';
        } else cout << xmin << ' ' << ymin << '\n';
    }
    return 0;
}