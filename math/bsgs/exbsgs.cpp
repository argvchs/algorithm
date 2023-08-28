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
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}
tuple<int, int, int> exgcd(int a, int b) {
    if (!b) return {1, 0, a};
    auto [x, y, res] = exgcd(b, a % b);
    return {y, x - a / b * y, res};
}
int inverse(int a, int p) { return (get<0>(exgcd(a, p)) + p) % p; }
int bsgs(int a, int b, int p) {
    M.clear();
    int n = sqrt(p) + 1, cur = b;
    for (int i = 0; i <= n; i++) {
        M[cur] = i;
        cur = (i64)cur * a % p;
    }
    int k = cur = quickpow(a, n, p);
    for (int i = 1; i <= n; i++) {
        if (M.count(cur)) return (i64)i * n - M[cur];
        cur = (i64)cur * k % p;
    }
    return -1;
}
int exbsgs(int a, int b, int p) {
    if (b == 1 || p == 1) return 0;
    int cnt = 0, cur = 1, gcd;
    while ((gcd = std::gcd(a, p)) != 1) {
        if (b % gcd) return -1;
        ++cnt, b /= gcd, p /= gcd;
        cur = (i64)cur * (a / gcd) % p;
        if (cur == b) return cnt;
    }
    int res = bsgs(a, (i64)b * inverse(cur, p) % p, p);
    if (res == -1) return -1;
    return res + cnt;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> a >> p >> b && a && b && p) {
        int res = exbsgs(a % p, b % p, p);
        if (res == -1) cout << "No Solution\n";
        else cout << res << '\n';
    }
    return 0;
}