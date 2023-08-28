#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 5e3 + 5, M = 5e4 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, dis[N], cur[N], head[N], cnt = 1, ansflow, anscost;
bool vis[N];
queue<int> Q;
struct edge {
    int to, next, w, c;
} e[M << 1];
void add(int u, int v, int w, int c) { e[++cnt] = {v, head[u], w, c}, head[u] = cnt; }
bool spfa() {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    dis[s] = 0, vis[s] = true;
    Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to, w = e[i].w, c = e[i].c;
            if (dis[v] > dis[u] + c && w) {
                dis[v] = dis[u] + c;
                if (!vis[v]) {
                    vis[v] = true, Q.push(v);
                    if (dis[Q.front()] > dis[Q.back()]) swap(Q.front(), Q.back());
                }
            }
        }
    }
    return dis[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    vis[u] = true;
    for (int &i = cur[u]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w, c = e[i].c;
        if (!vis[v] && dis[v] == dis[u] + c && w) {
            int res = dfs(v, min(flow - used, w));
            used += res, e[i].w -= res, e[i ^ 1].w += res;
            if (used == flow) break;
        }
    }
    vis[u] = false;
    return used;
}
void dinic() {
    int res;
    while (spfa()) {
        memcpy(cur, head, sizeof(cur));
        while ((res = dfs(s, INF))) ansflow += res, anscost += res * dis[t];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s >> t;
    for (int i = 1, u, v, w, c; i <= m; i++) {
        cin >> u >> v >> w >> c;
        add(u, v, w, c);
        add(v, u, 0, -c);
    }
    dinic();
    cout << ansflow << ' ' << anscost;
    return 0;
}