#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using m64 = pair<int, int>;
const int N = 5005, M = 5e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, h[N], dis[N], cur[N], head[N], cnt = 1, ansflow, anscost;
bool vis[N];
struct edge {
    int to, nex, w, c;
} e[M << 1];
queue<int> Q;
priority_queue<m64, vector<m64>, greater<>> PQ;
void add(int u, int v, int w, int c) { e[++cnt] = {v, head[u], w, c}, head[u] = cnt; }
void addflow(int u, int v, int w, int c) { add(u, v, w, c), add(v, u, 0, -c); }
void spfa() {
    memset(h, 0x3f, sizeof(h));
    h[s] = 0, vis[s] = true, Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w, c = e[i].c;
            if (h[v] > h[u] + c && w) {
                h[v] = h[u] + c;
                if (!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
}
bool dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    PQ.emplace(dis[s] = 0, s);
    while (!PQ.empty()) {
        int u = PQ.top().second;
        PQ.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w, c = e[i].c;
            if (dis[v] > dis[u] + c + h[u] - h[v] && w)
                dis[v] = dis[u] + c + h[u] - h[v], PQ.emplace(dis[v], v);
        }
    }
    return dis[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    vis[u] = true;
    for (int &i = cur[u]; i; i = e[i].nex) {
        int v = e[i].to, w = e[i].w, c = e[i].c;
        if (!vis[v] && dis[v] == dis[u] + c + h[u] - h[v] && w) {
            int ret = dfs(v, min(flow - used, w));
            used += ret, e[i].w -= ret, e[i ^ 1].w += ret;
            if (used == flow) break;
        }
    }
    vis[u] = false;
    return used;
}
void dinic() {
    int ret;
    spfa();
    while (dijkstra()) {
        memcpy(cur, head, sizeof(cur));
        memset(vis, 0, sizeof(vis));
        while ((ret = dfs(s, INF))) ansflow += ret, anscost += ret * (dis[t] + h[t]);
        for (int i = 1; i <= n; i++) h[i] += dis[i];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w, c; i <= m; i++) {
        cin >> u >> v >> w >> c;
        addflow(u, v, w, c);
    }
    dinic();
    cout << ansflow << ' ' << anscost;
    return 0;
}