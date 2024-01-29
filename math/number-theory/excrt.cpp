#include <iostream>
#include <tuple>
#include <utility>
using namespace std;
using i64 = long long;
using i64x2 = pair<i64, i64>;
using i64x3 = tuple<i64, i64, i64>;
using i128 = __int128;
int n;
i64 a, b, p = 1, q;
i64x3 exgcd(i64 a, i64 b) {
    if (!b) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}
i64x2 excrt(i64 a, i64 b, i64 p, i64 q) {
    auto [x, y, g] = exgcd(p, q);
    i64 l = (i128)p * q / g;
    x = ((i128)x * (b - a) / g + q / g) % (q / g);
    return {(p * x + a + l) % l, l};
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> q >> b;
        tie(a, p) = excrt(a, b, p, q);
    }
    cout << a;
}