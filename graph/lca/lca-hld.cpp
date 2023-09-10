#include <iostream>
using namespace std;
const int N = 5e5 + 5;
int n, m, s, fa[N], ch[N], dep[N], siz[N], top[N], head[N], cnt;
struct edge {
    int to, next;
} e[N << 1];
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void dfs1(int u, int fa) {
    ::fa[u] = fa, dep[u] = dep[fa] + 1, siz[u] = 1;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v != fa) {
            dfs1(v, u), siz[u] += siz[v];
            if (siz[v] > siz[ch[u]]) ch[u] = v;
        }
    }
}
void dfs2(int u, int fa, int top) {
    ::top[u] = top;
    if (!ch[u]) return;
    dfs2(ch[u], u, top);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (v != fa && v != ch[u]) dfs2(v, u, v);
    }
}
int lca(int u, int v) {
    while (top[u] != top[v])
        if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
        else v = fa[top[v]];
    return dep[u] < dep[v] ? u : v;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v; i <= n - 1; i++) {
        cin >> u >> v;
        addedge(u, v);
    }
    dfs1(s, 0), dfs2(s, 0, s);
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    return 0;
}