#include <iostream>
using namespace std;
const int N = 4e4 + 5;
int n, p[N], mu[N], cnt, ans;
bool vis[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n, mu[1] = 1;
    if (!--n) return cout << '0', 0;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) p[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
            vis[i * p[j]] = true;
            if (!(i % p[j])) break;
            mu[i * p[j]] = -mu[i];
        }
    }
    for (int i = 1; i <= n; i++) mu[i] += mu[i - 1];
    for (int i = 1, j; i <= n; i = j + 1)
        j = n / (n / i), ans += (n / i) * (n / j) * (mu[j] - mu[i - 1]);
    cout << ans + 2;
}