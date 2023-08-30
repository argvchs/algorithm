#include <iostream>
#include <random>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], rt[N], fa[N], siz[N], cnt;
bool vis[N];
mt19937 rnd(random_device{}());
struct node {
    int l, r;
    pair<int, int> val;
} tree[N];
int merge(int lt, int rt) {
    if (!lt || !rt) return lt ^ rt;
    if (tree[lt].val > tree[rt].val) swap(lt, rt);
    if (rnd() & 1) swap(tree[lt].l, tree[lt].r);
    tree[lt].l = merge(tree[lt].l, rt);
    return lt;
}
void insert(int &rt, pair<int, int> a) {
    tree[++cnt] = {0, 0, a};
    rt = merge(rt, cnt);
}
void remove(int &rt) { rt = merge(tree[rt].l, tree[rt].r); }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        fa[i] = i, siz[i] = 1;
        insert(rt[i], {a[i], i});
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
            auto [val, id] = tree[rt[u = find(u)]].val;
            remove(rt[u]);
            vis[id] = true;
            cout << val << '\n';
        }
    }
    return 0;
}