#include <cstring>
#include <iostream>
using namespace std;
constexpr int N = 5005, M = 2e5 + 5;
int n, m, fa[N], siz[N], cnt[0x10000], tot, ans;
struct edge {
    int from, to, w;
} e[M], tmp[M];
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
void unite(int u, int v) {
    if ((u = find(u)) == (v = find(v))) return;
    if (siz[u] < siz[v]) swap(u, v);
    fa[v] = u, siz[u] += siz[v];
}
bool check(int u, int v) { return find(u) == find(v); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> e[i].from >> e[i].to >> e[i].w;
    memcpy(tmp, e, sizeof(e));
    for (int i = 1; i <= m; i++) ++cnt[tmp[i].w & 0xffff];
    for (int i = 1; i <= 0xffff; i++) cnt[i] += cnt[i - 1];
    for (int i = m; i >= 1; i--) e[cnt[tmp[i].w & 0xffff]--] = tmp[i];
    memset(cnt, 0, sizeof(cnt));
    memcpy(tmp, e, sizeof(e));
    for (int i = 1; i <= m; i++) ++cnt[tmp[i].w >> 16 & 0xffff];
    for (int i = 1; i <= 0xffff; i++) cnt[i] += cnt[i - 1];
    for (int i = m; i >= 1; i--) e[cnt[tmp[i].w >> 16 & 0xffff]--] = tmp[i];
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for (int i = 1; i <= m; i++) {
        int u = e[i].from, v = e[i].to, w = e[i].w;
        if (!check(u, v)) ++tot, unite(u, v), ans += w;
    }
    if (tot == n - 1) cout << ans;
    else cout << "orz";
    return 0;
}