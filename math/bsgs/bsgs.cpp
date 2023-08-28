#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
using i64 = long long;
int a, b, p, ans;
unordered_map<int, int> M;
int quickpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}
int bsgs(int a, int b, int p) {
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
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> p >> a >> b;
    ans = bsgs(a % p, b % p, p);
    if (ans == -1) cout << "no solution";
    else cout << ans;
    return 0;
}