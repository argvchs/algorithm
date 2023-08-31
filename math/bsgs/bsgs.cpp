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
    int n = sqrt(p) + 1, k = quickpow(a, n, p);
    for (int i = 0, j = b; i <= n; i++, j = (i64)j * a % p) M[j] = i;
    for (int i = 1, j = k; i <= n; i++, j = (i64)j * k % p)
        if (M.count(j)) return (i64)i * n - M[j];
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