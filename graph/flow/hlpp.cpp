#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using m64 = pair<int, int>;
const int N = 1205, M = 12e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, ht[N], ex[N], gap[N], cur[N], head[N], cnt = 1;
bool vis[N];
struct edge {
    int to, next, w;
} e[M << 1];
queue<int> Q;
priority_queue<m64> PQ;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void addflow(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
bool bfs() {
    memset(ht, 0x3f, sizeof(ht));
    ht[t] = 0, vis[t] = true, Q.push(t);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to, w = e[i ^ 1].w;
            if (!vis[v] && w) ht[v] = ht[u] + 1, vis[v] = true, Q.push(v);
        }
    }
    return ht[s] != INF;
}
bool push(int u) {
    for (int &i = cur[u]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w;
        if ((u == s || ht[u] == ht[v] + 1) && ht[v] < n && w) {
            if (u != s) w = min(ex[u], e[i].w);
            if (v != t && !ex[v]) PQ.emplace(ht[v], v);
            ex[u] -= w, ex[v] += w, e[i].w -= w, e[i ^ 1].w += w;
            if (u != s && !ex[u]) return false;
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
    if (ht[u] < n) ++gap[ht[u]], PQ.emplace(ht[u], u);
}
void hlpp() {
    if (!bfs()) return;
    ht[s] = n;
    for (int i = 1; i <= n; i++)
        if (ht[i] < n) ++gap[ht[i]];
    memcpy(cur, head, sizeof(cur));
    push(s);
    while (!PQ.empty()) {
        int u = PQ.top().second;
        PQ.pop();
        if (!push(u)) continue;
        if (!--gap[ht[u]])
            for (int i = 1; i <= n; i++)
                if (i != s && ht[i] > ht[u]) ht[i] = n + 1;
        relabel(u);
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
    cout << ex[t];
    return 0;
}