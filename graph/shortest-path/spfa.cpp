#include <cstring>
#include <iostream>
#include <numeric>
#include <queue>
using namespace std;
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, dis[N];
bool vis[N];
vector<pair<int, int>> G[N];
queue<int> Q;
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = true;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (auto [v, w] : G[u])
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = true, Q.push(v);
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
    spfa();
    for (int i = 1; i <= n; i++)
        if (dis[i] == INF) cout << numeric_limits<int>::max() << ' ';
        else cout << dis[i] << ' ';
    return 0;
}