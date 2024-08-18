#include <algorithm>
#include <iostream>
using namespace std;
const int N = 5e3 + 5, M = 2e5 + 5;
int n, m, fa[N], siz[N], tot, ans;
struct edge {
    int from, to, w;
    bool operator<(edge x) { return w < x.w; }
} e[M];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> e[i].from >> e[i].to >> e[i].w;
    sort(e + 1, e + m + 1);
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for (int i = 1; i <= m; i++) {
        int u = e[i].from, v = e[i].to, w = e[i].w;
        if ((u = find(u)) == (v = find(v))) continue;
        if (siz[u] < siz[v]) swap(u, v);
        fa[v] = u, siz[u] += siz[v], ++tot, ans += w;
    }
    if (tot == n - 1) cout << ans;
    else cout << "orz";
}