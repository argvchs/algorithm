#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
const int N = 5e3 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, h[N], dis[N], cur[N], ansflow, anscost;
bool vis[N];
vector<tuple<int, int, int, int>> G[N];
queue<int> Q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> PQ;
void addflow(int u, int v, int w, int c) {
    G[u].emplace_back(v, w, +c, G[v].size());
    G[v].emplace_back(u, 0, -c, G[u].size() - 1);
}
void spfa() {
    memset(h, 0x3f, sizeof(h));
    memset(vis, 0, sizeof(vis));
    h[s] = 0, vis[s] = true;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (auto [v, w, c, rev] : G[u])
            if (h[v] > h[u] + c && w) {
                h[v] = h[u] + c;
                if (!vis[v]) vis[v] = true, Q.push(v);
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
        for (auto [v, w, c, rev] : G[u])
            if (dis[v] > dis[u] + c + h[u] - h[v] && w) {
                dis[v] = dis[u] + c + h[u] - h[v];
                PQ.emplace(dis[v], v);
            }
    }
    return dis[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    vis[u] = true;
    for (int &i = cur[u]; i < G[u].size(); i++) {
        auto [v, w, c, rev] = G[u][i];
        if (!vis[v] && dis[v] == dis[u] + c + h[u] - h[v] && w) {
            int res = dfs(v, min(flow - used, w));
            used += res, get<1>(G[u][i]) -= res, get<1>(G[v][rev]) += res;
            if (used == flow) break;
        }
    }
    vis[u] = false;
    return used;
}
void dinic() {
    int res;
    spfa();
    while (dijkstra()) {
        memset(vis, 0, sizeof(vis));
        memset(cur, 0, sizeof(cur));
        while ((res = dfs(s, INF))) ansflow += res, anscost += res * (dis[t] + h[t]);
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