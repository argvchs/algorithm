#include <iostream>
using namespace std;
using i64 = long long;
const int N = 4e4 + 5;
int n, p[N], phi[N], cnt, ans;
bool vis[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    if (n == 1) return cout << '0', 0;
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) p[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
            vis[i * p[j]] = true;
            phi[i * p[j]] = phi[i] * (p[j] - !!(i % p[j]));
            if (i % p[j] == 0) break;
        }
    }
    for (int i = 1; i <= n - 1; i++) ans += phi[i];
    cout << (ans << 1 | 1);
}