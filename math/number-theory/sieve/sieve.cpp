#include <iostream>
using namespace std;
const int N = 1e8 + 5;
int n, m, p[N], cnt;
bool vis[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) p[++cnt] = i;
        for (int j = 1; j <= cnt && i * p[j] <= n; j++) {
            vis[i * p[j]] = true;
            if (!(i % p[j])) break;
        }
    }
    for (int i = 1, x; i <= m; i++) cin >> x, cout << p[x] << '\n';
}