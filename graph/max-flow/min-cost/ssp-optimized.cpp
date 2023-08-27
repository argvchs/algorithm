#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
const int N = 5e3 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, dis[N], cur[N], ansflow, anscost;
bool vis[N];
vector<tuple<int, int, int, int>> G[N];
queue<int> Q;
void addflow(int u, int v, int w, int c) {
    int i = G[u].size(), j = G[v].size();
    G[u].emplace_back(v, w, +c, j);
    G[v].emplace_back(u, 0, -c, i);
}
bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0, vis[s] = true;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (auto [v, w, c, i] : G[u])
            if (dis[v] > dis[u] + c && w) {
                dis[v] = dis[u] + c;
                if (!vis[v]) {
                    vis[v] = true, Q.push(v);
                    if (dis[Q.front()] > dis[Q.back()]) swap(Q.front(), Q.back());
                }
            }
    }
    return dis[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    vis[u] = true;
    for (int &i = cur[u]; i < G[u].size(); i++) {
        auto [v, w, c, j] = G[u][i];
        if (!vis[v] && dis[v] == dis[u] + c && w) {
            int res = dfs(v, min(flow - used, w));
            used += res, get<1>(G[u][i]) -= res, get<1>(G[v][j]) += res;
            if (used == flow) break;
        }
    }
    vis[u] = false;
    return used;
}
void dinic() {
    int res;
    while (spfa()) {
        memset(cur, 0, sizeof(cur));
        while ((res = dfs(s, INF))) ansflow += res, anscost += res * dis[t];
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