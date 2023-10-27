#include <bit>
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;
using u32 = unsigned;
const int N = 1e5 + 5, M = 5e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, dis[N], pos[N], siz[32], head[N], cnt, beg, top;
bool vis[N];
struct edge {
    int to, next, w;
} e[M << 1];
vector<int> buc[32], tmp;
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
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
        while (pos[top = buc[0][beg]] == -1) ++beg;
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
    dis[top = s] = 0;
    for (int i = 1; i <= n; i++) insert(i);
    for (int i = 1; i <= n; i++, removemin())
        for (int j = head[top]; j; j = e[j].next) {
            int v = e[j].to, w = e[j].w;
            if (dis[v] > dis[top] + w) update(v, dis[top] + w);
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
    dijkstra();
    for (int i = 1; i <= n; i++)
        if (dis[i] == INF) cout << numeric_limits<int>::max() << ' ';
        else cout << dis[i] << ' ';
    return 0;
}