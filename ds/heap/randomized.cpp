#include <iostream>
#include <random>
using namespace std;
const int N = 1e5 + 5;
int n, m, rt[N], fa[N];
bool vis[N];
struct node {
    int l, r, val;
} t[N];
mt19937 gen(random_device{}());
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (lt > rt) swap(lt, rt);
    if (t[lt].val > t[rt].val) swap(lt, rt);
    if (gen() & 1) swap(t[lt].l, t[lt].r);
    t[lt].l = merge(t[lt].l, rt);
    return lt;
}
int removemin(int rt) { return merge(t[rt].l, t[rt].r); }
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> t[i].val;
    for (int i = 1; i <= n; i++) fa[i] = rt[i] = i;
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u;
        if (op == 1) {
            cin >> v;
            if (vis[u] || vis[v]) continue;
            if ((u = find(u)) == (v = find(v))) continue;
            fa[v] = u, rt[u] = merge(rt[u], rt[v]);
        } else if (!vis[u]) {
            vis[rt[u = find(u)]] = true;
            cout << t[rt[u]].val << '\n', rt[u] = removemin(rt[u]);
        } else cout << "-1\n";
    }
    return 0;
}