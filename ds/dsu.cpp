#include <iostream>
using namespace std;
const int N = 1e4 + 5;
int n, m, fa[N], siz[N];
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
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u >> v;
        if (op == 1) unite(u, v);
        else cout << (check(u, v) ? "Y\n" : "N\n");
    }
    return 0;
}