#include <cstring>
#include <iostream>
#include <numeric>
#include <queue>
using namespace std;
using u32 = unsigned;
using i64 = long long;
using m64 = pair<int, int>;
constexpr int N = 3e3 + 5, M = 6e3 + 5, INF = 0x3f3f3f3f;
int n, m, s, h[N], dis[N], tot[N], pos[N], siz[32], head[N], cnt, beg, top;
i64 ans;
bool vis[N];
struct edge {
    int to, next, w;
} e[M << 1];
queue<int> Q;
vector<int> buc[32], tmp;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
bool spfa() {
    memset(h, 0x3f, sizeof(h));
    h[n + 1] = 0, vis[n + 1] = true, Q.push(n + 1);
    for (int i = 1; i <= n; i++) add(n + 1, i, 0);
    while (!Q.empty()) {
        int u = Q.front();
        vis[u] = false, Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
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
    int k = bit_width<u32>(dis[u] ^ dis[top]);
    ++siz[k], pos[u] = buc[k].size(), buc[k].push_back(u);
}
void update(int u, int w) {
    int k = bit_width<u32>(dis[u] ^ dis[top]);
    --siz[k], dis[u] = w;
    int t = bit_width<u32>(dis[u] ^ dis[top]);
    ++siz[t], pos[u] = buc[t].size(), buc[t].push_back(u);
}
void removemin() {
    pos[top] = -1;
    if (--siz[0]) {
        while (pos[top = buc[0][beg]] != beg) ++beg;
        return;
    }
    int cur = 0, pre = top;
    for (int i = 30; i >= 1; i--)
        if (siz[i]) cur = i;
    siz[cur] = beg = top = 0, tmp.swap(buc[cur]);
    for (int i = 0; i <= cur; i++) buc[i].clear();
    for (int i = 0; i < (int)tmp.size(); i++) {
        int k = bit_width<u32>(dis[tmp[i]] ^ dis[pre]);
        if (k == cur && pos[tmp[i]] == i && dis[tmp[i]] <= dis[top]) top = tmp[i];
    }
    for (int i = 0; i < (int)tmp.size(); i++) {
        int k = bit_width<u32>(dis[tmp[i]] ^ dis[pre]);
        if (k == cur && pos[tmp[i]] == i) insert(tmp[i]);
    }
}
void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    dis[top = s] = beg = 0;
    for (int i = 0; i <= 30; i++) buc[i].clear();
    for (int i = 1; i <= n; i++) insert(i);
    for (int i = 1; i <= n; i++, removemin())
        for (int j = head[top]; j; j = e[j].next) {
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
            if (dis[j] == INF) ans += (i64)j * (int)1e9;
            else ans += (i64)j * (dis[j] + h[j] - h[s]);
        cout << ans << '\n';
    }
    return 0;
}