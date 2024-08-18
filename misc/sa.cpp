#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
using namespace std;
using f64 = double;
const int N = 1e3 + 5;
const f64 EPS = 1e-3;
int n, a[N], b[N], c[N];
f64 xans, yans, ans;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution urd;
f64 calc(f64 x, f64 y) {
    f64 ret = 0;
    for (int i = 1; i <= n; i++)
        ret += c[i] * sqrt((x - a[i]) * (x - a[i]) + (y - b[i]) * (y - b[i]));
    if (ret < ans) ans = ret, xans = x, yans = y;
    return ret;
}
void sa() {
    f64 x = xans, y = yans, t = 1e3;
    while (t > EPS) {
        f64 z = x + (urd(rng) * 2 - 1) * t;
        f64 w = y + (urd(rng) * 2 - 1) * t;
        f64 de = calc(z, w) - calc(x, y);
        if (exp(-de / t) > urd(rng)) x = z, y = w;
        t *= 0.99;
    }
    for (int i = 1; i <= 1e3; i++) {
        f64 z = xans + (urd(rng) * 2 - 1) * t;
        f64 w = yans + (urd(rng) * 2 - 1) * t;
        calc(z, w);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= n; i++) xans += a[i], yans += b[i];
    ans = calc(xans /= n, yans /= n);
    sa(), sa(), sa();
    cout << fixed << setprecision(3) << xans << ' ' << yans;
}