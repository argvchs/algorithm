#include <iostream>
#include <utility>
using namespace std;
const int N = 2e5 + 5;
int n, m, fa[N], siz[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u >> v;
        if (op == 1) {
            if ((u = find(u)) == (v = find(v))) continue;
            if (siz[u] < siz[v]) swap(u, v);
            fa[v] = u, siz[u] += siz[v];
        } else cout << (find(u) == find(v) ? "Y\n" : "N\n");
    }
}