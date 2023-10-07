#include <iomanip>
#include <iostream>
#include <random>
using namespace std;
using f80 = long double;
const int N = 1005;
const f80 A = 0.99, EPS = 1e-7;
int n, a[N], b[N], c[N];
f80 ansx, ansy, ansz = __builtin_infl();
mt19937 gen(random_device{}());
uniform_real_distribution<f80> dist;
f80 calc(f80 x, f80 y) {
    f80 ret = 0;
    for (int i = 1; i <= n; i++) {
        f80 xx = x - a[i], yy = y - b[i];
        ret += (sqrt(xx * xx + yy * yy)) * c[i];
    }
    if (ret < ansz) ansx = x, ansy = y, ansz = ret;
    return ret;
}
void solve() {
    f80 x = ansx, y = ansy;
    for (f80 t = 1000; t > EPS; t *= A) {
        f80 xx = ansx + (dist(gen) * 2 - 1) * t;
        f80 yy = ansy + (dist(gen) * 2 - 1) * t;
        f80 delta = calc(xx, yy) - calc(x, y);
        if (exp(-delta / t) > dist(gen)) x = xx, y = yy;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i];
    for (int i = 1; i <= 3; i++) solve();
    cout << fixed << setprecision(3) << ansx << ' ' << ansy;
    return 0;
}