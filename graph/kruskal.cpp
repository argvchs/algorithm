#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
const int N = 5005;
int n, m, fa[N], siz[N], cnt, ans;
vector<tuple<int, int, int>> E;
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        E.emplace_back(w, u, v);
    }
    sort(E.begin(), E.end());
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for (auto [w, u, v] : E) {
        u = find(u), v = find(v);
        if (u == v) continue;
        if (siz[u] < siz[v]) swap(u, v);
        fa[v] = u, siz[u] += siz[v];
        ++cnt, ans += w;
    }
    if (cnt == n - 1) cout << ans;
    else cout << "orz";
    return 0;
}