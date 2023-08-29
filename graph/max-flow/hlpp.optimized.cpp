#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
const int N = 1205, M = 12e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, ht[N], ex[N], gap[N], cur[N], head[N], cnt = 1, top;
bool vis[N];
queue<int> Q;
stack<int> S[N];
struct edge {
    int to, next, w;
} e[M << 1];
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
bool bfs() {
    memset(ht, 0x3f, sizeof(ht));
    ht[t] = 0, vis[t] = true;
    Q.push(t);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to, w = e[i ^ 1].w;
            if (!vis[v] && w) {
                ht[v] = ht[u] + 1, vis[v] = true;
                Q.push(v);
            }
        }
    }
    return ht[s] != INF;
}
bool push(int u) {
    for (int &i = cur[u]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w;
        if (ht[u] == ht[v] + 1 && w) {
            int flow = min(ex[u], w);
            if (v != s && v != t && !ex[v]) {
                top = max(top, ht[v]);
                S[ht[v]].push(v);
            }
            ex[u] -= flow, ex[v] += flow, e[i].w -= flow, e[i ^ 1].w += flow;
            if (!ex[u]) return false;
        }
    }
    cur[u] = head[u];
    return true;
}
void relabel(int u) {
    ht[u] = INF;
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (e[i].w) ht[u] = min(ht[u], ht[v] + 1);
    }
    if (ht[u] < n) {
        ++gap[ht[u]], top = max(top, ht[u]);
        S[ht[u]].push(u);
    }
}
void hlpp() {
    if (!bfs()) return;
    ht[s] = n;
    for (int i = 1; i <= n; i++)
        if (ht[i] != INF) ++gap[ht[i]];
    for (int i = head[s]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w;
        if (ht[v] != INF && w) {
            if (v != s && v != t && !ex[v]) {
                top = max(top, ht[v]);
                S[ht[v]].push(v);
            }
            ex[v] += w, e[i].w -= w, e[i ^ 1].w += w;
        }
    }
    memcpy(cur, head, sizeof(cur));
    while (top) {
        int u = S[top].top();
        S[top].pop();
        if (push(u)) {
            if (!--gap[ht[u]])
                for (int i = 1; i <= n; i++)
                    if (i != s && ht[i] > ht[u]) ht[i] = n + 1;
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
        add(u, v, w);
        add(v, u, 0);
    }
    hlpp();
    cout << ex[t];
    return 0;
}