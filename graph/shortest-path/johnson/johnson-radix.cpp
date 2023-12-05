#include <bit>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using u32 = unsigned;
using i64 = long long;
using p32 = pair<int, int>;
const int N = 3e3 + 5, M = 6e3 + 5, INF = 0x3f3f3f3f;
int n, m, s, h[N], dis[N], tot[N], pos[N], head[N], cnt, top;
i64 ans;
bool vis[N];
struct edge {
    int to, nex, w;
} e[M << 1];
queue<int> Q;
vector<int> buc[35];
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
bool spfa() {
    memset(h, 0x3f, sizeof(h));
    h[n + 1] = 0, vis[n + 1] = true, Q.push(n + 1);
    for (int i = 1; i <= n; i++) add(n + 1, i, 0);
    while (Q.size()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].nex) {
            int v = e[i].to, w = e[i].w;
            if (h[v] > h[u] + w) {
                h[v] = h[u] + w;
                if (vis[v]) continue;
                vis[v] = true, Q.push(v);
                if (++tot[v] == n + 1) return false;
            }
        }
    }
    return true;
}
void insert(int x) {
    int k = bit_width<u32>(dis[x] ^ dis[top]);
    pos[x] = buc[k].size(), buc[k].push_back(x);
}
void remove(int x) {
    int k = bit_width<u32>(dis[x] ^ dis[top]);
    buc[k][pos[x]] = buc[k].back();
    pos[buc[k].back()] = pos[x], buc[k].pop_back();
}
void update(int x, int k) { remove(x), dis[x] = k, insert(x); }
void removemin() {
    remove(top), top = 0;
    if (buc[0].size()) return void(top = buc[0][0]);
    for (int i = 1; i <= 30; i++) {
        if (buc[i].empty()) continue;
        for (int j : buc[i])
            if (dis[j] < dis[top]) top = j;
        for (int j : buc[i]) insert(j);
        return buc[i].clear();
    }
}
void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    dis[top = s] = 0;
    for (int i = 0; i <= 30; i++) buc[i].clear();
    for (int i = 1; i <= n; i++) insert(i);
    for (int i = 1; i <= n; i++, removemin()) {
        if (dis[top] == INF) break;
        for (int j = head[top]; j; j = e[j].nex) {
            int v = e[j].to, w = e[j].w;
            if (dis[v] > dis[top] + w + h[top] - h[v])
                update(v, dis[top] + w + h[top] - h[v]);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        add(u, v, w);
    }
    if (!spfa()) return cout << "-1", 0;
    for (int i = 1; i <= n; i++) {
        s = i, ans = 0, dijkstra();
        for (int j = 1; j <= n; j++)
            if (dis[j] == INF) ans += j * (i64)1e9;
            else ans += (i64)j * (dis[j] + h[j] - h[s]);
        cout << ans << '\n';
    }
    return 0;
}