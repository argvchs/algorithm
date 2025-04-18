#include <iostream>
#include <utility>
using namespace std;
const int N = 5e5 + 5;
int n, m, rt, fa[N], ch[N], siz[N], dep[N], top[N], head[N], cnt;
struct edge {
    int to, nxt;
} e[N << 1];
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void dfs1(int u, int fa) {
    ::fa[u] = fa, dep[u] = dep[fa] + 1, siz[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa) continue;
        dfs1(v, u), siz[u] += siz[v];
        if (siz[v] > siz[ch[u]]) ch[u] = v;
    }
}
void dfs2(int u, int fa, int top) {
    ::top[u] = top;
    if (!ch[u]) return;
    dfs2(ch[u], u, top);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v != fa && v != ch[u]) dfs2(v, u, v);
    }
}
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> rt;
    for (int i = 1, u, v; i <= n - 1; i++) cin >> u >> v, addedge(u, v);
    dfs1(rt, 0), dfs2(rt, 0, rt);
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, cout << lca(u, v) << '\n';
}