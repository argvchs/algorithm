#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int N = 1e5 + 5, M = 5e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, dis[N], head[N], cnt;
bool vis[N];
struct edge {
    int to, nxt, w;
} e[M];
queue<int> Q;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void spfa() {
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, vis[s] = true, Q.push(s);
    while (Q.size()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    spfa();
    for (int i = 1; i <= n; i++)
        if (dis[i] == INF) cout << 0x7fffffff << ' ';
        else cout << dis[i] << ' ';
    return 0;
}