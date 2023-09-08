#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], rt[N], fa[N], siz[N], cnt;
bool vis[N];
struct node {
    int l, r, val, id;
} tree[N];
auto cmp = [](node a, node b) {
    if (a.val != b.val) return a.val < b.val;
    return a.id < b.id;
};
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (cmp(tree[rt], tree[lt])) swap(lt, rt);
    tree[rt].r = tree[lt].l, tree[lt].l = rt;
    return lt;
}
int pairing(int rt) {
    if (!rt || !tree[rt].r) return rt;
    int r1 = tree[rt].r, r2 = tree[r1].r;
    tree[rt].r = tree[r1].r = 0;
    return merge(merge(rt, r1), pairing(r2));
}
int insert(int rt, int x, int y) {
    tree[++cnt] = {0, 0, x, y};
    return merge(rt, cnt);
}
int remove(int rt) { return pairing(tree[rt].l); }
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        fa[i] = i, siz[i] = 1;
        rt[i] = insert(rt[i], a[i], i);
    }
    for (int i = 1, op, u, v; i <= m; i++) {
        cin >> op >> u;
        if (op == 1) {
            cin >> v;
            if (vis[u] || vis[v]) continue;
            u = find(u), v = find(v);
            if (u == v) continue;
            if (siz[u] < siz[v]) swap(u, v);
            fa[v] = u, siz[u] += siz[v];
            rt[u] = merge(rt[u], rt[v]);
        } else {
            if (vis[u]) {
                cout << "-1\n";
                continue;
            }
            u = find(u);
            vis[tree[rt[u]].id] = true;
            cout << tree[rt[u]].val << '\n';
            rt[u] = remove(rt[u]);
        }
    }
    return 0;
}