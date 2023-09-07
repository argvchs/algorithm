#include <cmath>
#include <iostream>
#include <numeric>
#include <tuple>
#include <unordered_map>
using namespace std;
using i64 = long long;
int a, b, p;
unordered_map<int, int> M;
int quickpow(int a, int b, int p) {
    int ret = 1;
    while (b) {
        if (b & 1) ret = (i64)ret * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return ret;
}
auto exgcd(int a, int b) {
    if (!b) return make_tuple(1, 0, a);
    auto [x, y, gcd] = exgcd(b, a % b);
    return make_tuple(y, x - a / b * y, gcd);
}
int inverse(int a, int p) { return (get<0>(exgcd(a, p)) + p) % p; }
int bsgs(int a, int b, int p) {
    int n = sqrt(p) + 1, k = quickpow(a, n, p);
    M.clear();
    for (int i = 0, j = b; i <= n; i++, j = (i64)j * a % p) M[j] = i;
    for (int i = 1, j = k; i <= n; i++, j = (i64)j * k % p)
        if (M.count(j)) return (i64)i * n - M[j];
    return -1;
}
int exbsgs(int a, int b, int p) {
    if (b == 1 || p == 1) return 0;
    int cnt = 0, sum = 1, gcd;
    while ((gcd = std::gcd(a, p)) != 1) {
        if (b % gcd) return -1;
        ++cnt, b /= gcd, p /= gcd;
        sum = (i64)sum * (a / gcd) % p;
        if (sum == b) return cnt;
    }
    int ret = bsgs(a, (i64)b * inverse(sum, p) % p, p);
    if (ret == -1) return -1;
    return ret + cnt;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> a >> p >> b && a && b && p) {
        int ret = exbsgs(a % p, b % p, p);
        if (ret == -1) cout << "No Solution\n";
        else cout << ret << '\n';
    }
    return 0;
}