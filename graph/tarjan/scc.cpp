#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, a[N], b[N], dfn[N], low[N], belong[N], deg[N], dis[N], head[N], idx, cnt, tot, ans;
bool vis[N];
struct edge {
    int from, to, next;
} e[M << 1];
void add(int u, int v) { e[++cnt] = {u, v, head[u]}, head[u] = cnt; }
stack<int> S;
queue<int> Q;
void tarjan(int u) {
    dfn[u] = low[u] = ++idx, vis[u] = true;
    S.push(u);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
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
            dis[i] = b[i];
            Q.push(i);
        }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
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
        add(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    memset(head, 0, sizeof(head));
    cnt = 0;
    for (int i = 1; i <= m; i++) {
        int u = e[i].from, v = e[i].to;
        if (belong[u] != belong[v]) {
            add(belong[u], belong[v]);
            ++deg[belong[v]];
        }
    }
    toposort();
    for (int i = 1; i <= tot; i++) ans = max(ans, dis[i]);
    cout << ans;
    return 0;
}