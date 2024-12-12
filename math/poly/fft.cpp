#include <algorithm>
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;
using f64 = double;
using c64 = complex<f64>;
const int N = 3e6 + 5;
const f64 PI = acos(-1);
int n, m, lim = 1;
c64 a[N], b[N], w[N];
void dit(c64 *a, int n) {
    for (int i = 1; i < n; i <<= 1)
        for (int j = 0; j < n; j += i << 1)
            for (int k = 0; k < i; k++) {
                c64 x = a[j + k], y = a[j + k + i] * w[i + k];
                a[j + k] = x + y, a[j + k + i] = x - y;
            }
    reverse(a + 1, a + n);
    for (int i = 0; i < n; i++) a[i] /= n;
}
void dif(c64 *a, int n) {
    for (int i = n >> 1; i; i >>= 1)
        for (int j = 0; j < n; j += i << 1)
            for (int k = 0; k < i; k++) {
                c64 x = a[j + k], y = a[j + k + i];
                a[j + k] = x + y, a[j + k + i] = (x - y) * w[i + k];
            }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];
    while (lim <= n + m) lim <<= 1;
    c64 wn = exp(PI / (lim >> 1) * 1i);
    w[lim >> 1] = 1;
    for (int i = (lim >> 1) + 1; i < lim; i++) w[i] = w[i - 1] * wn;
    for (int i = (lim >> 1) - 1; i; i--) w[i] = w[i << 1];
    dif(a, lim), dif(b, lim);
    for (int i = 0; i < lim; i++) a[i] *= b[i];
    dit(a, lim);
    for (int i = 0; i <= n + m; i++) cout << (int)round(a[i].real()) << ' ';
}