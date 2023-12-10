#include <cmath>
#include <iostream>
using namespace std;
using f64 = double;
const int N = 15;
const f64 EPS = 1e-7;
int n;
f64 l, r, a[N];
f64 calc(f64 x) {
    f64 ret = 0;
    for (int i = 0; i <= n; i++) ret += a[i] * pow(x, i);
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> l >> r;
    for (int i = n; i >= 0; i--) cin >> a[i];
    while (r - l > EPS) {
        f64 mid = (l + r) / 2;
        if (calc(mid - EPS) < calc(mid + EPS)) l = mid;
        else r = mid;
    }
    cout << l;
    return 0;
}