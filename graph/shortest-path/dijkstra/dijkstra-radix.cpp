#include <bit>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
using u32 = unsigned;
const int N = 1e5 + 5, M = 5e5 + 5, INF = 0x3f3f3f3f;
int n, m, s, dis[N], pos[N], head[N], cnt, top;
struct edge {
    int to, nxt, w;
} e[M];
vector<int> buc[31];
void add(int u, int v, int w) { e[++cnt] = {v, head[u], w}, head[u] = cnt; }
void insert(int x) {
    int k = bit_width<u32>(dis[x] ^ dis[top]);
    pos[x] = buc[k].size(), buc[k].push_back(x);
}
void remove(int x) {
    int k = bit_width<u32>(dis[x] ^ dis[top]);
    pos[buc[k].back()] = pos[x];
    buc[k][pos[x]] = buc[k].back(), buc[k].pop_back();
}
void update(int x, int k) { remove(x), dis[x] = k, insert(x); }
void removemin() {
    remove(top), top = 0;
    if (buc[0].size()) return void(top = buc[0][0]);
    for (int i = 1; i < 31; i++) {
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
    for (int i = 1; i <= n; i++) insert(i);
    for (; top; removemin())
        for (int i = head[top]; i; i = e[i].nxt) {
            int v = e[i].to, w = e[i].w;
            if (dis[v] > dis[top] + w) update(v, dis[top] + w);
        }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> s;
    for (int i = 1, u, v, w; i <= m; i++) cin >> u >> v >> w, add(u, v, w);
    dijkstra();
    for (int i = 1; i <= n; i++)
        if (dis[i] == INF) cout << 0x7fffffff << ' ';
        else cout << dis[i] << ' ';
}