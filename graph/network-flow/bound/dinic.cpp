#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 2e3 + 5, M = 1e6 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, ss, tt, a[N], dep[N], cur[N], head[N], cnt, sum, ans;
bool vis[N];
struct edge {
    int to, nxt, w;
} e[M << 1];
queue<int> Q;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void addflow(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
void addflow(int u, int v, int l, int r) { a[u] -= l, a[v] += l, addflow(u, v, r - l); }
bool bfs() {
    memset(dep, 0x3f, sizeof(dep));
    memset(vis, 0, sizeof(vis));
    dep[s] = 1, vis[s] = true, Q.push(s);
    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (!vis[v] && w) dep[v] = dep[u] + 1, vis[v] = true, Q.push(v);
        }
    }
    return dep[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    for (int &i = cur[u]; i; i = e[i].nxt) {
        int v = e[i].to, w = e[i].w;
        if (dep[v] == dep[u] + 1 && w) {
            int ret = dfs(v, min(flow - used, w));
            used += ret, e[i].w -= ret, e[i ^ 1].w += ret;
            if (used == flow) break;
        }
    }
    return used;
}
void dinic() {
    while (bfs()) {
        memcpy(cur, head, sizeof(cur));
        int ret;
        while ((ret = dfs(s, INF))) ans += ret;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        memset(head, 0, sizeof(head));
        memset(a, 0, sizeof(a));
        cnt = 1, sum = ans = 0;
        s = n + m + 1, t = s + 1, ss = s + 2, tt = s + 3;
        for (int i = 1, x; i <= m; i++) cin >> x, addflow(i + n, t, x, INF);
        for (int i = 1, x, y, z, l, r; i <= n; i++) {
            cin >> x >> y, addflow(s, i, y);
            for (int j = 1; j <= x; j++) cin >> z >> l >> r, addflow(i, z + n + 1, l, r);
        }
        for (int i = 1; i <= t; i++)
            if (a[i] > 0) addflow(ss, i, a[i]), sum += a[i];
            else addflow(i, tt, -a[i]);
        addflow(t, s, INF);
        swap(s, ss), swap(t, tt), dinic();
        if (ans != sum) {
            cout << "-1\n\n";
            continue;
        }
        sum = e[cnt].w, ans = e[cnt].w = e[cnt ^ 1].w = 0;
        swap(s, ss), swap(t, tt), dinic();
        cout << sum + ans << "\n\n";
    }
    return 0;
}