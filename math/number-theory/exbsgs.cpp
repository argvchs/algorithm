#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
using namespace std;
using i64 = long long;
int a, b, p;
unordered_map<int, int> M;
int qpow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % p)
        if (b & 1) ret = (i64)ret * a % p;
    return ret;
}
int exbsgs(int a, int b, int p) {
    if (b == 1 || p == 1) return 0;
    int x = 1, y = 0, g;
    while ((g = gcd(a, p)) != 1) {
        if (b % g) return -1;
        b /= g, p /= g, x = (i64)x * a / g % p, ++y;
        if (b == x) return y;
    }
    M.clear();
    int n = ceil(sqrt(p)), m = qpow(a, n, p);
    for (int i = 0; i != n; i++, b = (i64)b * a % p) M[b] = i;
    for (int i = 0; i <= n; i++, x = (i64)x * m % p)
        if (M.count(x) && i * n >= M[x]) return i * n - M[x] + y;
    return -1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> a >> p >> b && a && b && p) {
        int ans = exbsgs(a % p, b % p, p);
        if (ans == -1) cout << "No Solution\n";
        else cout << ans << '\n';
    }
    return 0;
}