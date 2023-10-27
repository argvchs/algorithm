#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using i64 = long long;
const int N = 205, M = 5005, INF = 0x3f3f3f3f;
int n, m, s, t, dep[N], cur[N], head[N], cnt = 1;
i64 ans;
bool vis[N];
struct edge {
    int to, next, w;
} e[M << 1];
queue<int> Q;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void addflow(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
bool bfs() {
    memset(dep, 0x3f, sizeof(dep));
    memset(vis, 0, sizeof(vis));
    dep[s] = 1, vis[s] = true, Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to, w = e[i].w;
            if (!vis[v] && w) dep[v] = dep[u] + 1, vis[v] = true, Q.push(v);
        }
    }
    return dep[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    for (int &i = cur[u]; i; i = e[i].next) {
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
    int ret;
    while (bfs()) {
        memcpy(cur, head, sizeof(cur));
        while ((ret = dfs(s, INF))) ans += ret;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        addflow(u, v, w);
    }
    dinic();
    cout << ans;
    return 0;
}