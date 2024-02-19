#include <algorithm>
#include <bit>
#include <iostream>
using namespace std;
using u32 = unsigned;
const int N = 5e5 + 5;
int n, m, rt, a[N], f[N][25], dep[N], dfn[N], head[N], idx, cnt;
struct edge {
    int to, nxt;
} e[N << 1];
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void dfs(int u, int fa) {
    a[dfn[u] = ++idx] = u, f[idx][0] = dfn[fa];
    for (int i = head[u]; i; i = e[i].nxt)
        if (e[i].to != fa) dfs(e[i].to, u);
}
int lca(int u, int v) {
    if (u == v) return u;
    if ((u = dfn[u]) > (v = dfn[v])) swap(u, v);
    int k = bit_width<u32>(v - u++) - 1;
    return a[min(f[u][k], f[v - (1 << k) + 1][k])];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> rt;
    for (int i = 1, u, v; i <= n - 1; i++) cin >> u >> v, addedge(u, v);
    dfs(rt, 0);
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, cout << lca(u, v) << '\n';
}