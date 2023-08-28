#include <iostream>
using namespace std;
const int N = 1e8 + 5;
int n, t, p[N], pre[N], cnt, ans;
bool vis[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 2; i <= 1e8; i++) {
        if (!vis[i]) p[++cnt] = pre[i] = i;
        for (int j = 1; j <= cnt && i * p[j] <= 1e8; j++) {
            vis[i * p[j]] = true;
            pre[i * p[j]] = p[j];
            if (i % p[j] == 0) break;
        }
    }
    cin >> t;
    while (t--) {
        cin >> n;
        ans = 0;
        while (n != 1) ans ^= pre[n], n /= pre[n];
        cout << ans << '\n';
    }
    return 0;
}