#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
int n, m, dis[N][N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << dis[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}