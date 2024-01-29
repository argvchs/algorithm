#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 105;
int n, m, f[N][N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    memset(f, 0x3f, sizeof(f));
    cin >> n >> m;
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        f[u][v] = f[v][u] = min(f[u][v], w);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << f[i][j] << ' ';
        cout << '\n';
    }
}