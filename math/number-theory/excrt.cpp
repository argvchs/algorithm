#include <iostream>
using namespace std;
using i64 = long long;
using i128 = __int128;
int n;
i64 a, b, p = 1, q;
i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (!b) return x = 1, y = 0, a;
    i64 ret = exgcd(b, a % b, y, x);
    return y -= a / b * x, ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> q >> b;
        i64 x, y, g = exgcd(p, q, x, y);
        i64 l = (i128)p * q / g;
        x = ((i128)x * (b - a) / g + q / g) % (q / g);
        a = (p * x + a + l) % l, p = l;
    }
    cout << a;
    return 0;
}