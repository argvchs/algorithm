#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;
using f80 = long double;
const int N = 1e3 + 5;
const f80 EPS = 1e-4;
int n, a[N], b[N], c[N];
f80 x, y, ans;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<f80> dist;
f80 calc(f80 x, f80 y) {
    f80 ret = 0;
    for (int i = 1; i <= n; i++) {
        f80 xx = x - a[i];
        f80 yy = y - b[i];
        ret += c[i] * sqrt(xx * xx + yy * yy);
    }
    if (ret < ans) ans = ret, ::x = x, ::y = y;
    return ret;
}
void solve() {
    f80 x = ::x, y = ::y, t = 1e3;
    while (t > EPS) {
        f80 xx = x + (dist(rng) * 2 - 1) * t;
        f80 yy = y + (dist(rng) * 2 - 1) * t;
        f80 de = calc(xx, yy) - calc(x, y);
        if (exp(-de / t) > dist(rng)) x = xx, y = yy;
        t *= 0.99;
    }
    for (int i = 1; i <= 1e3; i++) {
        f80 xx = ::x + (dist(rng) * 2 - 1) * t;
        f80 yy = ::y + (dist(rng) * 2 - 1) * t;
        calc(xx, yy);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= n; i++) x += a[i], y += b[i];
    ans = calc(x /= n, y /= n);
    solve(), solve(), solve();
    cout << fixed << setprecision(3) << x << ' ' << y;
    return 0;
}