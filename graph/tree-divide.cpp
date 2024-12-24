#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1e4 + 5, V = 1e7 + 5;
int n, m, rt, a[N], w[N], siz[N], dis[N], head[N], cnt, tot;
bool vis1[N], vis2[V], ans[N];
vector<int> tmp1, tmp2;
struct edge {
    int to, nxt, w;
} e[N << 1];
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void addedge(int u, int v, int w) { add(u, v, w), add(v, u, w); }
void dfs1(int u, int fa) {
    siz[u] = 1, w[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (v == fa || vis1[v]) continue;
        dfs1(v, u), siz[u] += siz[v], w[u] = max(w[u], siz[v]);
    }
    w[u] = max(w[u], tot - siz[u]);
    if (w[u] < w[rt]) rt = u;
}
void dfs2(int u, int fa) {
    tmp1.push_back(dis[u]);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (v != fa && !vis1[v]) dis[v] = dis[u] + w, dfs2(v, u);
    }
}
void solve(int u) {
    vis1[u] = vis2[0] = true, tmp1.push_back(0);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (vis1[v]) continue;
        dis[v] = w, dfs2(v, u);
        for (int j : tmp1)
            for (int k = 1; k <= m; k++)
                if (a[k] >= j && vis2[a[k] - j]) ans[k] = true;
        for (int j : tmp1)
            if (j <= 1e7) tmp2.push_back(j), vis2[j] = true;
        tmp1.clear();
    }
    for (int i : tmp2) vis2[i] = false;
    tmp2.clear();
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!vis1[v]) rt = 0, tot = siz[v], dfs1(v, 0), solve(rt);
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= n - 1; i++) cin >> u >> v >> w, addedge(u, v, w);
    for (int i = 1; i <= m; i++) cin >> a[i];
    rt = 0, tot = w[0] = n, dfs1(1, 0), solve(rt);
    for (int i = 1; i <= m; i++) cout << (ans[i] ? "AYE\n" : "NAY\n");
}