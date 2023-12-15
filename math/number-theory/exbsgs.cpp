#include <cmath>
#include <iostream>
#include <numeric>
#include <unordered_map>
using namespace std;
using i64 = long long;
int a, b, p;
unordered_map<int, int> M;
int exbsgs(int a, int b, int p) {
    if (b == 1 || p == 1) return 0;
    int m = sqrt(p) + 1, x = 1, y = 0, c = 1, g;
    while ((g = gcd(a, p)) != 1) {
        if (b % g) return -1;
        b /= g, p /= g, x = (i64)x * (a / g) % p, ++y;
        if (b == x) return y;
    }
    M.clear();
    for (int i = 0; i != m; i++, c = (i64)c * a % p) M[(i64)c * b % p] = i;
    for (int i = 0; i <= m; i++, x = (i64)x * c % p)
        if (M.count(x) && i * m >= M[x]) return i * m - M[x] + y;
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