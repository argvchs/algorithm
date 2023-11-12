#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
using u32 = unsigned;
using i64 = long long;
using m64 = pair<int, int>;
const int N = 3005, M = 6005, INF = 0x3f3f3f3f;
int n, m, s, h[N], dis[N], tot[N], pos[N], siz[32], head[N], cnt, beg, top;
i64 ans;
bool vis[N];
struct edge {
    int to, nex, w;
} e[M << 1];
queue<int> Q;
vector<int> buc[32], tmp;
int bitlen(int x) { return x ? 32 - __builtin_clz(x) : 0; }
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
bool spfa() {
    memset(h, 0x3f, sizeof(h));
    h[n + 1] = 0, vis[n + 1] = true, Q.push(n + 1);
    for (int i = 1; i <= n; i++) add(n + 1, i, 0);
    while (!Q.empty()) {
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
void insert(int u) {
    int x = bitlen(dis[u] ^ dis[top]);
    ++siz[x], pos[u] = buc[x].size(), buc[x].push_back(u);
}
void update(int u, int w) {
    int x = bitlen(dis[u] ^ dis[top]);
    --siz[x], dis[u] = w;
    int y = bitlen(dis[u] ^ dis[top]);
    ++siz[y], pos[u] = buc[y].size(), buc[y].push_back(u);
}
void removemin() {
    pos[top] = -1;
    if (--siz[0]) {
        while (pos[top = buc[0][beg]] == -1) ++beg;
        return;
    }
    int cur = 0, las = top;
    for (int i = 30; i >= 1; i--)
        if (siz[i]) cur = i;
    siz[cur] = beg = top = 0, tmp.swap(buc[cur]);
    for (int i = 0; i <= cur; i++) buc[i].clear();
    auto st = tmp.begin(), ed = tmp.end();
    for (auto it = st; it != ed; ++it) {
        int x = bitlen(dis[*it] ^ dis[las]);
        if (x == cur && pos[*it] == it - st && dis[*it] <= dis[top]) top = *it;
    }
    for (auto it = st; it != ed; ++it) {
        int x = bitlen(dis[*it] ^ dis[las]);
        if (x == cur && pos[*it] == it - st) insert(*it);
    }
}
void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    dis[top = s] = beg = 0;
    for (int i = 0; i <= 30; i++) buc[i].clear();
    for (int i = 1; i <= n; i++) insert(i);
    for (int i = 1; i <= n; i++, removemin())
        for (int j = head[top]; j; j = e[j].nex) {
            int v = e[j].to, w = e[j].w;
            if (dis[v] > dis[top] + w + h[top] - h[v])
                update(v, dis[top] + w + h[top] - h[v]);
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