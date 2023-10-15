#include <iostream>
using namespace std;
constexpr int N = 1e5 + 5;
int n, m, a[N], rt[N], fa[N], siz[N], cnt;
bool vis[N];
struct node {
    int l, r, val, id;
} t[N];
auto cmp = [](node a, node b) {
    if (a.val != b.val) return a.val < b.val;
    return a.id < b.id;
};
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (cmp(t[rt], t[lt])) swap(lt, rt);
    t[rt].r = t[lt].l, t[lt].l = rt;
    return lt;
}
int pairing(int rt) {
    if (!rt || !t[rt].r) return rt;
    int r1 = t[rt].r, r2 = t[r1].r;
    t[rt].r = t[r1].r = 0;
    return merge(merge(rt, r1), pairing(r2));
}
int insert(int rt, int x, int y) {
    t[++cnt] = {0, 0, x, y};
    return merge(rt, cnt);
}
int removemin(int rt) { return pairing(t[rt].l); }
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        fa[i] = i, siz[i] = 1, rt[i] = insert(rt[i], a[i], i);
    }
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u;
        if (op == 1) {
            cin >> v;
            if (vis[u] || vis[v]) continue;
            if ((u = find(u)) == (v = find(v))) continue;
            if (siz[u] < siz[v]) swap(u, v);
            fa[v] = u, siz[u] += siz[v], rt[u] = merge(rt[u], rt[v]);
        } else if (!vis[u]) {
            vis[t[rt[u = find(u)]].id] = true;
            cout << t[rt[u]].val << '\n', rt[u] = removemin(rt[u]);
        } else cout << "-1\n";
    }
    return 0;
}