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
    int k = quickpow(a, siz, p);
    for (int i = 0, j = b; i <= siz; i++, j = (i64)j * a % p) M[j] = i;
    for (int i = 1, j = k; i <= siz; i++, j = (i64)j * k % p)
        if (M.count(j)) {
            ans = (i64)i * siz - M[j];
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