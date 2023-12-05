#include <iostream>
using namespace std;
using i64 = long long;
int a, b, p;
int qpow(int a, int b, int p) {
    int ret = 1;
    for (int i = b; i; i >>= 1, a = (i64)a * a % p)
        if (i & 1) ret = (i64)ret * a % p;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << qpow(a, b, p);
    return 0;
}