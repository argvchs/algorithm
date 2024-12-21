#include <algorithm>
#include <iostream>
using namespace std;
using i64 = long long;
int n;
i64 x, p[63], ans;
void insert(i64 x) {
    for (int i = 62; i >= 0; i--) {
        if (!(x & (1ll << i))) continue;
        if (!p[i]) return void(p[i] = x);
        x ^= p[i];
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x, insert(x);
    for (int i = 62; i >= 0; i--) ans = max(ans, ans ^ p[i]);
    cout << ans;
}