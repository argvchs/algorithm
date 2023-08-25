#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 1205, INF32 = 0x3f3f3f3f;
const i64 INF64 = 0x3f3f3f3f3f3f3f3f;
int n, m, s, t, h[N], gap[N << 1];
i64 e[N], ans;
bool vis[N];
vector<tuple<int, i64, int>> G[N];
queue<int> Q;
priority_queue<pair<int, int>> PQ;
void addflow(int u, int v, i64 w) {
    G[u].emplace_back(v, w, G[v].size());
    G[v].emplace_back(u, 0, G[u].size() - 1);
}
bool bfs() {
    memset(h, 0x3f, sizeof(h));
    h[t] = 0, vis[t] = true;
    Q.push(t);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto [v, w, rev] : G[u])
            if (!vis[v] && get<1>(G[v][rev])) {
                h[v] = h[u] + 1, vis[v] = true;
                Q.push(v);
            }
    }
    return h[s] != INF32;
}
bool push(int u) {
    for (auto &[v, w, rev] : G[u])
        if (vis[v] && (u == s || h[u] == h[v] + 1) && w) {
            i64 flow = min(e[u], w);
            if (v != s && v != t && !e[v]) PQ.emplace(h[v], v);
            e[u] -= flow, e[v] += flow, w -= flow, get<1>(G[v][rev]) += flow;
            if (!e[u]) return false;
        }
    return true;
}
void relabel(int u) {
    h[u] = INF32;
    for (auto [v, w, rev] : G[u])
        if (vis[v] && w) h[u] = min(h[u], h[v] + 1);
    if (h[u] < n) {
        ++gap[h[u]];
        PQ.emplace(h[u], u);
    }
}
void hlpp() {
    if (!bfs()) return;
    h[s] = n, e[s] = INF64;
    for (int i = 1; i <= n; i++)
        if (vis[i]) ++gap[h[i]];
    push(s);
    while (!PQ.empty()) {
        int u = PQ.top().second;
        PQ.pop();
        if (push(u)) {
            if (!--gap[h[u]])
                for (int i = 1; i <= n; i++)
                    if (vis[i] && i != s && h[i] > h[u]) h[i] = n + 1;
            relabel(u);
        }
    }
    ans = e[t];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        addflow(u, v, w);
    }
    hlpp();
    cout << ans;
    return 0;
}