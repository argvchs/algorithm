#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;
using i64 = long long;
int a, b, p, siz, ans;
unordered_map<int, int> M;
int quickpow(int a, int b, int p) {
    int res = 1;
    while (b) {
        if (b & 1) res = (i64)res * a % p;
        a = (i64)a * a % p, b >>= 1;
    }
    return res;
}
bool bsgs(int a, int b, int p) {
    siz = sqrt(p) + 1;
    int y = quickpow(a, siz, p);
    for (int i = 0, x = b; i <= siz; i++, x = (i64)x * a % p) M[x] = i;
    for (int i = 1, x = y; i <= siz; i++, x = (i64)x * y % p)
        if (M.contains(x)) {
            ans = (i64)i * siz - M[x];
            return true;
        }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> p >> a >> b;
    if (bsgs(a, b, p)) cout << ans;
    else cout << "no solution";
    return 0;
}