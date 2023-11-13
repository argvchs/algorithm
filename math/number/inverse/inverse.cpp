#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
using t32 = tuple<int, int, int>;
int n, p;
int quickpow(int a, int b, int p) {
    int ret = 1;
    for (int i = b; i; i >>= 1, a = (i64)a * a % p)
        if (i & 1) ret = (i64)ret * a % p;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cout << quickpow(i, p - 2, p) << '\n';
    return 0;
}