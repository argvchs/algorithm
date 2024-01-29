#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 205, M = 2e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, ss, tt, a[N], dep[N], cur[N], head[N], cnt = 1, sum, ans;
bool vis[N];
struct edge {
    int to, nxt, w;
} e[M << 1];
queue<int> Q;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void addflow(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
bool bfs() {
    memset(dep, 0x3f, sizeof(dep));
    memset(vis, false, sizeof(vis));
    dep[s] = 1, vis[s] = true, Q.push(s);
    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (!vis[v] && w) dep[v] = dep[u] + 1, vis[v] = true, Q.push(v);
        }
    }
    return dep[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    for (int &i = cur[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (dep[v] == dep[u] + 1 && w) {
            int ret = dfs(v, min(flow - used, w));
            used += ret, e[i].w -= ret, e[i ^ 1].w += ret;
            if (used == flow) break;
        }
    }
    return used;
}
void dinic() {
    while (bfs()) {
        memcpy(cur, head, sizeof(cur));
        int ret;
        while ((ret = dfs(s, INF))) ans += ret;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t, ss = n + 1, tt = n + 2;
    for (int i = 1, u, v, l, r; i <= m; i++) {
        cin >> u >> v >> l >> r;
        a[u] -= l, a[v] += l, addflow(u, v, r - l);
    }
    for (int i = 1; i <= n; i++)
        if (a[i] > 0) addflow(ss, i, a[i]), sum += a[i];
        else addflow(i, tt, -a[i]);
    addflow(t, s, INF);
    swap(s, ss), swap(t, tt), dinic();
    if (ans != sum) return cout << "please go home to sleep", 0;
    sum = e[cnt].w, ans = e[cnt].w = e[cnt ^ 1].w = 0;
    swap(s, ss), swap(t, tt), dinic();
    cout << sum + ans;
}