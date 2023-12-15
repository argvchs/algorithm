#include <algorithm>
#include <iostream>
#include <stack>
using namespace std;
const int N = 2e4 + 5, M = 1e5 + 5;
int n, m, dfn[N], low[N], head[N], idx, cnt, tot;
bool vis[N];
struct edge {
    int to, nxt;
} e[M << 1];
stack<int> S;
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx, S.push(u);
    int cnt = !!fa;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) ++cnt;
        } else low[u] = min(low[u], dfn[v]);
    }
    if (cnt >= 2) vis[u] = true, ++tot;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, addedge(u, v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
    cout << tot << '\n';
    for (int i = 1; i <= n; i++)
        if (vis[i]) cout << i << ' ';
    return 0;
}