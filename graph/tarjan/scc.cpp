#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
using namespace std;
const int N = 1e4 + 5;
int n, m, a[N], b[N], dfn[N], low[N], belong[N], deg[N], dis[N], idx, tot, ans;
bool vis[N];
vector<int> G[N], H[N];
vector<pair<int, int>> E;
stack<int> S;
queue<int> Q;
void tarjan(int u) {
    dfn[u] = low[u] = ++idx, vis[u] = true;
    S.push(u);
    for (int v : G[u])
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    if (dfn[u] == low[u]) {
        ++tot;
        while (S.top() != u) {
            int v = S.top();
            b[belong[v] = tot] += a[v], vis[v] = false;
            S.pop();
        }
        b[belong[u] = tot] += a[u], vis[u] = false;
        S.pop();
    }
}
void toposort() {
    for (int i = 1; i <= tot; i++)
        if (!deg[i]) {
            Q.push(i);
            dis[i] = b[i];
        }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : H[u]) {
            dis[v] = max(dis[v], dis[u] + b[v]);
            if (!--deg[v]) Q.push(v);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        E.emplace_back(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (auto [u, v] : E)
        if (belong[u] != belong[v]) {
            H[belong[u]].push_back(belong[v]);
            ++deg[belong[v]];
        }
    toposort();
    for (int i = 1; i <= tot; i++) ans = max(ans, dis[i]);
    cout << ans;
    return 0;
}