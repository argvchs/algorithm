#include <complex>
#include <iostream>
using namespace std;
using f64 = double;
using c64 = complex<f64>;
const int N = 3e6 + 5;
const f64 PI = acos(-1);
int n, m, r[N], lim = 1, cnt;
c64 f[N], g[N];
void fft(c64 a[], int t) {
    for (int i = 0; i < lim; i++)
        if (i < r[i]) swap(a[i], a[r[i]]);
    for (int i = 1; i < lim; i <<= 1) {
        c64 rt(cos(PI / i), t * sin(PI / i));
        for (int j = 0; j < lim; j += i << 1) {
            c64 w(1, 0);
            for (int k = 0; k < i; k++, w *= rt) {
                c64 x = a[j + k], y = a[j + k + i] * w;
                a[j + k] = x + y, a[j + k + i] = x - y;
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> f[i];
    for (int i = 0; i <= m; i++) cin >> g[i];
    while (lim <= n + m) lim <<= 1, ++cnt;
    for (int i = 0; i < lim; i++) r[i] = r[i >> 1] >> 1 | (i & 1) << (cnt - 1);
    fft(f, 1), fft(g, 1);
    for (int i = 0; i < lim; i++) f[i] *= g[i];
    fft(f, -1);
    for (int i = 0; i <= n + m; i++) cout << (int)(f[i].real() / lim + 0.5) << ' ';
    return 0;
}