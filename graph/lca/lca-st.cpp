#include <algorithm>
#include <bit>
#include <iostream>
using namespace std;
using u32 = unsigned;
const int N = 5e5 + 5;
int n, m, rt, a[N << 1], f[N << 1][25], dep[N], dfn[N], head[N], idx, cnt;
struct edge {
    int to, nxt;
} e[N << 1];
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void dfs(int u, int fa) {
    dfn[u] = ++idx, a[idx] = u;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v != fa) dfs(v, u), a[++idx] = u;
    }
}
int lca(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    int k = bit_width<u32>(r - l + 1) - 1;
    return a[min(f[l][k], f[r - (1 << k) + 1][k])];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> rt;
    for (int i = 1, u, v; i <= n - 1; i++) cin >> u >> v, addedge(u, v);
    dfs(rt, 0);
    for (int i = 1; i <= n << 1; i++) f[i][0] = dfn[a[i]];
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n << 1; i++)
            f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
}