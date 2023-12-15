#include <iostream>
using namespace std;
using i64 = long long;
int T, a, b, c;
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) return x = 1, y = 0, a;
    i64 ret = exgcd(b, a % b, y, x);
    return y -= a / b * x, ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        cin >> a >> b >> c;
        i64 x, y, g = exgcd(a, b, x, y);
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
    return 0;
}