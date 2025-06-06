#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using i64 = long long;
const int N = 3e3 + 5, M = 9e3 + 5, INF = 0x3f3f3f3f;
int n, m, s, ss, h[N], dis[N], tot[N], head[N], cnt;
i64 ans;
bool vis[N];
struct edge {
    int to, nxt, w;
} e[M];
queue<int> Q;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> PQ;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
bool spfa() {
    memset(h, 0x3f, sizeof(h));
    h[ss] = 0, vis[ss] = true, Q.push(ss);
    while (Q.size()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                if (vis[v]) continue;
                vis[v] = true, Q.push(v);
                if (++tot[v] == n + 1) return false;
            }
        }
    }
    return true;
}
void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    PQ.emplace(dis[s] = 0, s);
    while (PQ.size()) {
        int u = PQ.top().second;
        PQ.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (dis[v] > dis[u] + w + h[u] - h[v]) PQ.emplace(dis[v] = dis[u] + w + h[u] - h[v], v);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m, ss = n + 1;
    for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, add(u, v, w);
    for (int i = 1; i <= n; i++) add(ss, i, 0);
    if (!spfa()) return cout << "-1", 0;
    for (int i = 1; i <= n; i++) {
        s = i, ans = 0, dijkstra();
        for (int j = 1; j <= n; j++)
            if (dis[j] == INF) ans += j * (i64)1e9;
            else ans += (i64)j * (dis[j] + h[j] - h[s]);
        cout << ans << '\n';
    }
}