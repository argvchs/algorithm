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
int query(int l, int r) {
    int k = bit_width<u32>(r - l + 1) - 1;
    int x = f[l][k], y = f[r - (1 << k) + 1][k];
    return dfn[x] < dfn[y] ? x : y;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> rt;
    for (int i = 1, u, v; i <= n - 1; i++) cin >> u >> v, addedge(u, v);
    dfs(rt, 0);
    for (int i = 1; i <= idx; i++) f[i][0] = a[i];
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= idx; i++) {
            int x = f[i][j - 1], y = f[i + (1 << (j - 1))][j - 1];
            f[i][j] = dfn[x] < dfn[y] ? x : y;
        }
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (dfn[u] > dfn[v]) swap(u, v);
        cout << query(dfn[u], dfn[v]) << '\n';
    }
    return 0;
}