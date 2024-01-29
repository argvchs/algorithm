#include <algorithm>
#include <complex>
#include <iostream>
using namespace std;
using f64 = double;
using c64 = complex<f64>;
const int N = 3e6 + 5;
const f64 PI = acos(-1);
int n, m, r[N], lim = 1, cnt;
c64 f[N], g[N], w[N];
void fft(c64 f[], int t) {
    for (int i = 0; i < lim; i++)
        if (i < r[i]) swap(f[i], f[r[i]]);
    for (int i = 1; i < lim; i <<= 1)
        for (int j = 0; j < lim; j += i << 1)
            for (int k = 0; k < i; k++) {
                c64 x = f[j + k], y = f[j + k + i] * w[i + k];
                f[j + k] = x + y, f[j + k + i] = x - y;
            }
    if (t == 1) return;
    reverse(f + 1, f + lim);
    for (int i = 0; i < lim; i++) f[i] /= lim;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> f[i];
    for (int i = 0; i <= m; i++) cin >> g[i];
    while (lim <= n + m) lim <<= 1, ++cnt;
    c64 wn = exp(PI / (lim >> 1) * 1i);
    w[lim >> 1] = 1;
    for (int i = (lim >> 1) + 1; i < lim; i++) w[i] = w[i - 1] * wn;
    for (int i = (lim >> 1) - 1; i > 0; i--) w[i] = w[i << 1];
    for (int i = 0; i < lim; i++) r[i] = r[i >> 1] >> 1 | (i & 1) << (cnt - 1);
    fft(f, 1), fft(g, 1);
    for (int i = 0; i < lim; i++) f[i] *= g[i];
    fft(f, -1);
    for (int i = 0; i <= n + m; i++) cout << (int)round(f[i].real()) << ' ';
}