#include <iostream>
using namespace std;
using i64 = long long;
int a, b, p;
int quickpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << quickpow(a, b, p);
    return 0;
}