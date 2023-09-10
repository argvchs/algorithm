#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
using i64 = long long;
int a, b, p, ans;
unordered_map<int, int> M;
int quickpow(int a, int b, int p) {
    int ret = 1;
    for (int i = b; i; i >>= 1, a = (i64)a * a % p)
        if (i & 1) ret = (i64)ret * a % p;
    return ret;
}
int bsgs(int a, int b, int p) {
    int n = sqrt(p) + 1, x = quickpow(a, n, p);
    for (int i = 0, j = b; i <= n; i++, j = (i64)j * a % p) M[j] = i;
    for (int i = 1, j = x; i <= n; i++, j = (i64)j * x % p)
        if (M.contains(j)) return i * n - M[j];
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