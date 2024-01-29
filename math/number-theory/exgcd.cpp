#include <iostream>
using namespace std;
using i64 = long long;
using i64x3 = tuple<i64, i64, i64>;
int T, a, b, c;
i64x3 exgcd(i64 a, i64 b) {
    if (!b) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
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
            cout << (xmax - xmin) / b + 1 << ' ';
            cout << xmin << ' ' << ymin << ' ';
            cout << xmax << ' ' << ymax << '\n';
        } else cout << xmin << ' ' << ymin << '\n';
    }
}