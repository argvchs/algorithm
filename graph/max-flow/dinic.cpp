#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 205, INF = 0x3f3f3f3f;
int n, m, s, t, dep[N], cur[N];
i64 ans;
bool vis[N];
vector<tuple<int, i64, int>> G[N];
queue<int> Q;
void addflow(int u, int v, i64 w) {
    G[u].emplace_back(v, w, G[v].size());
    G[v].emplace_back(u, 0, G[u].size() - 1);
}
bool bfs() {
    memset(dep, 0x3f, sizeof(dep));
    memset(vis, 0, sizeof(vis));
    dep[s] = 1, vis[s] = true;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto [v, w, rev] : G[u])
            if (!vis[v] && w) {
                dep[v] = dep[u] + 1, vis[v] = true;
                Q.push(v);
            }
    }
    return dep[t] != INF;
}
int dfs(int u, i64 flow) {
    if (u == t) return flow;
    i64 used = 0;
    for (int &i = cur[u]; i < G[u].size(); i++) {
        auto [v, w, rev] = G[u][i];
        if (dep[v] == dep[u] + 1 && w) {
            i64 res = dfs(v, min(flow - used, w));
            used += res, get<1>(G[u][i]) -= res, get<1>(G[v][rev]) += res;
            if (used == flow) break;
        }
    }
    return used;
}
void dinic() {
    int res;
    while (bfs()) {
        memset(cur, 0, sizeof(cur));
        while ((res = dfs(s, INF))) ans += res;
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