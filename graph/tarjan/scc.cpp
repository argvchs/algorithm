#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, a[N], b[N], dfn[N], low[N], bel[N], deg[N], dis[N], head[N], idx, cnt, tot, ans;
bool vis[N];
struct edge {
    int from, to, nxt;
} e[M];
queue<int> Q;
stack<int> S;
void add(int u, int v) { e[++cnt] = {u, v, head[u]}, head[u] = cnt; }
void tarjan(int u) {
    dfn[u] = low[u] = ++idx, vis[u] = true, S.push(u);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] != low[u]) return;
    int top = ++tot;
    do {
        top = S.top(), S.pop();
        b[bel[top] = tot] += a[top], vis[top] = false;
    } while (top != u);
}
void toposort() {
    for (int i = 1; i <= tot; i++)
        if (!deg[i]) dis[i] = b[i], Q.push(i);
    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            dis[v] = max(dis[v], dis[u] + b[v]);
            if (!--deg[v]) Q.push(v);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, add(u, v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    memset(head, 0, sizeof(head)), cnt = 0;
    for (int i = 1; i <= m; i++) {
        int u = e[i].from, v = e[i].to;
        if (bel[u] != bel[v]) ++deg[bel[v]], add(bel[u], bel[v]);
    }
    toposort();
    for (int i = 1; i <= tot; i++) ans = max(ans, dis[i]);
    cout << ans;
}