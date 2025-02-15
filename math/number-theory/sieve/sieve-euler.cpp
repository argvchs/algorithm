#include <iostream>
using namespace std;
const int N = 4e4 + 5;
int n, p[N], phi[N], cnt, ans;
bool vis[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n, phi[1] = 1;
    if (!--n) return cout << '0', 0;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) p[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
            vis[i * p[j]] = true;
            phi[i * p[j]] = phi[i] * (p[j] - !!(i % p[j]));
            if (!(i % p[j])) break;
        }
    }
    for (int i = 1; i <= n; i++) ans += phi[i];
    cout << (ans << 1 | 1);
}