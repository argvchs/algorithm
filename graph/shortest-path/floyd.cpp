#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using i64 = long long;
const int N = 105;
int n, m, dis[N][N];
i64 ans;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j) dis[i][j] = 1e9;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for (int i = 1; i <= n; i++) {
        ans = 0;
        for (int j = 1; j <= n; j++) ans += (i64)j * dis[i][j];
        cout << ans << '\n';
    }
    return 0;
}