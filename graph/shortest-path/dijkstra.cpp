#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, dis[N];
bool vis[N];
vector<pair<int, int>> G[N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> Q;
void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    Q.emplace(dis[s] = 0, s);
    while (!Q.empty()) {
        int u = Q.top().second;
        Q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto [v, w] : G[u])
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                Q.emplace(dis[v], v);
            }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        G[u].emplace_back(v, w);
    }
    dijkstra();
    for (int i = 1; i <= n; i++)
        if (dis[i] == INF) cout << numeric_limits<int>::max() << ' ';
        else cout << dis[i] << ' ';
    return 0;
}