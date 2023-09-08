#include <iostream>
#include <random>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], rt[N], fa[N], siz[N], cnt;
bool vis[N];
struct node {
    int l, r, val, id;
} tree[N];
mt19937 rng(random_device{}());
auto cmp = [](node a, node b) {
    if (a.val != b.val) return a.val < b.val;
    return a.id < b.id;
};
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (cmp(tree[rt], tree[lt])) swap(lt, rt);
    if (rng() & 1) swap(tree[lt].l, tree[lt].r);
    tree[lt].l = merge(tree[lt].l, rt);
    return lt;
}
int insert(int rt, int x, int y) {
    tree[++cnt] = {0, 0, x, y};
    return merge(rt, cnt);
}
int remove(int rt) { return merge(tree[rt].l, tree[rt].r); }
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