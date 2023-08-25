#include <iostream>
#include <vector>
using namespace std;
const int N = 5e5 + 5;
int n, m, s, fa[N], dep[N], siz[N], ch[N], top[N];
vector<int> G[N];
void dfs1(int u, int fa) {
    ::fa[u] = fa, dep[u] = dep[fa] + 1, siz[u] = 1;
    for (int v : G[u])
        if (v != fa) {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[ch[u]]) ch[u] = v;
        }
}
void dfs2(int u, int top) {
    ::top[u] = top;
    if (!ch[u]) return;
    dfs2(ch[u], top);
    for (int v : G[u])
        if (v != fa[u] && v != ch[u]) dfs2(v, v);
}
int lca(int u, int v) {
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
        else v = fa[top[v]];
    if (dep[u] < dep[v]) return u;
    return v;
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
    dfs1(s, 0);
    dfs2(s, s);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    return 0;
}