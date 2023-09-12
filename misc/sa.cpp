#include <iostream>
#include <random>
using namespace std;
using f80 = long double;
const int N = 1005;
const f80 A = 0.99, EPS = 1e-7;
int n, a[N], b[N], c[N];
f80 ansx, ansy, ansz = __builtin_infl();
mt19937 rng(random_device{}());
uniform_real_distribution<f80> dist;
f80 calc(f80 x, f80 y) {
    f80 ret = 0;
    for (int i = 1; i <= n; i++) {
        f80 nx = x - a[i], ny = y - b[i];
        ret += (sqrt(nx * nx + ny * ny)) * c[i];
    }
    if (ret < ansz) ansx = x, ansy = y, ansz = ret;
    return ret;
}
void solve() {
    f80 x = ansx, y = ansy;
    for (f80 t = 1000; t > EPS; t *= A) {
        f80 nx = ansx + (dist(rng) * 2 - 1) * t;
        f80 ny = ansy + (dist(rng) * 2 - 1) * t;
        f80 delta = calc(nx, ny) - calc(x, y);
        if (exp(-delta / t) > dist(rng)) x = nx, y = ny;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= 3; i++) solve();
    cout.setf(ios::fixed);
    cout.precision(3);
    cout << ansx << ' ' << ansy;
    return 0;
}