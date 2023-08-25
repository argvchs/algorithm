#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 1205, INF32 = 0x3f3f3f3f;
const i64 INF64 = 0x3f3f3f3f3f3f3f3f;
int n, m, s, t, dep[N], gap[N << 1], top;
i64 ans[N];
bool vis[N];
vector<tuple<int, i64, int>> G[N];
queue<int> Q;
stack<int> S[N << 1];
void addflow(int u, int v, i64 w) {
    G[u].emplace_back(v, w, G[v].size());
    G[v].emplace_back(u, 0, G[u].size() - 1);
}
bool bfs() {
    memset(dep, 0x3f, sizeof(dep));
    dep[t] = 0, vis[t] = true;
    Q.push(t);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto [v, w, rev] : G[u])
            if (!vis[v] && get<1>(G[v][rev])) {
                dep[v] = dep[u] + 1, vis[v] = true;
                Q.push(v);
            }
    }
    return dep[s] != INF32;
}
bool push(int u) {
    for (auto &[v, w, rev] : G[u])
        if (vis[v] && (u == s || dep[u] == dep[v] + 1) && w) {
            i64 flow = min(ans[u], w);
            if (v != s && v != t && !ans[v]) {
                top = max(top, dep[v]);
                S[dep[v]].push(v);
            }
            ans[u] -= flow, ans[v] += flow, w -= flow, get<1>(G[v][rev]) += flow;
            if (!ans[u]) return false;
        }
    return true;
}
void relabel(int u) {
    dep[u] = INF32;
    for (auto [v, w, rev] : G[u])
        if (vis[v] && w) dep[u] = min(dep[u], dep[v] + 1);
    if (dep[u] < n) {
        top = max(top, dep[u]), ++gap[dep[u]];
        S[dep[u]].push(u);
    }
}
void hlpp() {
    if (!bfs()) return;
    dep[s] = n, ans[s] = INF64;
    for (int i = 1; i <= n; i++)
        if (vis[i]) ++gap[dep[i]];
    push(s);
    while (top) {
        int u = S[top].top();
        S[top].pop();
        if (push(u)) {
            if (!--gap[dep[u]])
                for (int i = 1; i <= n; i++)
                    if (vis[i] && i != s && dep[i] > dep[u]) dep[i] = n + 1;
            relabel(u);
        }
        while (!S[top].size() && top) --top;
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
    hlpp();
    cout << ans[t];
    return 0;
}