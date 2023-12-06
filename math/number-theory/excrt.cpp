#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
using i128 = __int128;
using p64 = pair<i64, i64>;
using t64 = tuple<i64, i64, i64>;
int n;
i64 a, b, p = 1, q;
t64 exgcd(i64 a, i64 b) {
    if (!b) return {1, 0, a};
    auto [x, y, g] = exgcd(b, a % b);
    return {y, x - a / b * y, g};
}
p64 excrt(i64 a, i64 b, i64 p, i64 q) {
    auto [x, y, g] = exgcd(p, q);
    i64 l = (i128)p * q / g;
    x = ((i128)x * (b - a) / g + q / g) % (q / g);
    return {(p * x + a + l) % l, l};
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> q >> b;
        tie(a, p) = excrt(a, b, p, q);
    }
    cout << a;
    return 0;
}