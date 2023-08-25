#include <iostream>
#include <vector>
using namespace std;
const int N = 1e6 + 5;
int n, m, s, f[N][25], dep[N];
vector<int> G[N];
void dfs(int u, int fa) {
    f[u][0] = fa, dep[u] = dep[fa] + 1;
    for (int i = 1; i <= 20; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int v : G[u])
        if (v != fa) dfs(v, u);
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; i >= 0; i--)
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    if (u == v) return u;
    for (int i = 20; i >= 0; i--)
        if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    return f[u][0];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v; i <= n - 1; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(s, 0);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    return 0;
}