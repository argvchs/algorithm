#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 2005, M = 1e6 + 5, INF = 0x3f3f3f3f;
int n, m, s, t, s1, t1, s2, t2, inf[N], ouf[N], dep[N], cur[N], head[N], cnt, sum, ans;
bool vis[N];
struct edge {
    int to, next, w;
} e[M << 1];
queue<int> Q;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void addflow(int u, int v, int w) { add(u, v, w), add(v, u, 0); }
bool bfs() {
    memset(dep, 0x3f, sizeof(dep));
    memset(vis, 0, sizeof(vis));
    dep[s] = 1, vis[s] = true, Q.push(s);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to, w = e[i].w;
            if (!vis[v] && w) dep[v] = dep[u] + 1, vis[v] = true, Q.push(v);
        }
    }
    return dep[t] != INF;
}
int dfs(int u, int flow) {
    if (u == t) return flow;
    int used = 0;
    for (int &i = cur[u]; i; i = e[i].next) {
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
    int ret;
    while (bfs()) {
        memcpy(cur, head, sizeof(cur));
        while ((ret = dfs(s, INF))) ans += ret;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m) {
        memset(head, 0, sizeof(head));
        memset(inf, 0, sizeof(inf));
        memset(ouf, 0, sizeof(ouf));
        cnt = 1, sum = ans = 0;
        s1 = n + m + 1, t1 = n + m + 2;
        s2 = n + m + 3, t2 = n + m + 4;
        for (int i = 1, w; i <= m; i++) {
            cin >> w;
            inf[t1] += w, ouf[i + n] += w;
            addflow(i + n, t1, INF - w);
        }
        for (int i = 1, k, w; i <= n; i++) {
            cin >> k >> w;
            addflow(s1, i, w);
            for (int j = 1, u, l, r; j <= k; j++) {
                cin >> u >> l >> r;
                inf[u + n + 1] += l, ouf[i] += l;
                addflow(i, u + n + 1, r - l);
            }
        }
        for (int i = 1; i <= n + m + 2; i++)
            if (inf[i] > ouf[i]) {
                sum += inf[i] - ouf[i];
                addflow(s2, i, inf[i] - ouf[i]);
            } else addflow(i, t2, ouf[i] - inf[i]);
        addflow(t1, s1, INF);
        s = s2, t = t2, dinic();
        if (ans != sum) {
            cout << "-1\n\n";
            continue;
        }
        sum = e[cnt].w;
        ans = e[cnt].w = e[cnt ^ 1].w = 0;
        s = s1, t = t1, dinic();
        cout << sum + ans << "\n\n";
    }
    return 0;
}