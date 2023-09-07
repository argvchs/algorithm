#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
int n;
i64 a, p = 1, ai, pi;
auto exgcd(i64 a, i64 b) {
    if (!b) return make_tuple(1ll, 0ll, a);
    auto [x, y, gcd] = exgcd(b, a % b);
    return make_tuple(y, x - a / b * y, gcd);
}
auto excrt(i64 a1, i64 p1, i64 a2, i64 p2) {
    auto [x, y, gcd] = exgcd(p1, p2);
    i64 lcm = p1 * p2 / gcd;
    x = (x * (a2 - a1) / gcd + p2 / gcd) % (p2 / gcd);
    return make_pair((p1 * x + a1 + lcm) % lcm, lcm);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> pi >> ai;
        tie(a, p) = excrt(a, p, ai, pi);
    }
    cout << a;
    return 0;
}