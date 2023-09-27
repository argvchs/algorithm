#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
using i128 = __int128;
int n;
i64 a, p = 1, aa, pp;
tuple<i64, i64, i64> exgcd(i64 a, i64 b) {
    if (!b) return {1, 0, a};
    auto [x, y, gcd] = exgcd(b, a % b);
    return {y, x - a / b * y, gcd};
}
pair<i64, i64> excrt(i64 a1, i64 p1, i64 a2, i64 p2) {
    auto [x, y, gcd] = exgcd(p1, p2);
    i64 lcm = (i128)p1 * p2 / gcd;
    x = ((i128)x * (a2 - a1) / gcd + p2 / gcd) % (p2 / gcd);
    return {(p1 * x + a1 + lcm) % lcm, lcm};
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pp >> aa;
        tie(a, p) = excrt(a, p, aa, pp);
    }
    cout << a;
    return 0;
}