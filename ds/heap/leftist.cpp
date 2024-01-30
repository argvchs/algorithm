#include <iostream>
#include <utility>
using namespace std;
const int N = 1e5 + 5;
int n, m, rt[N], fa[N];
bool vis[N];
struct node {
    int l, r, val, dis;
} t[N];
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (t[lt].val > t[rt].val)  swap(lt, rt);
    t[lt].l = merge(t[lt].l, rt);
    if (t[t[lt].l].dis > t[t[lt].r].dis) swap(t[lt].l, t[lt].r);
    t[lt].dis = t[t[lt].r].dis + 1;
    return lt;
}
void removemin(int &rt) { rt = merge(t[rt].l, t[rt].r); }
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
    ios_base::sync_with_stdio(false);
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
            cout << t[rt[u]].val << '\n', removemin(rt[u]);
        } else cout << "-1\n";
    }
}