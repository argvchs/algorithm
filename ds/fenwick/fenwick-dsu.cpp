#include <cmath>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, fa[N];
i64 a[N], bit[N];
int find(int u) { return u == fa[u] ? u : fa[u] = find(fa[u]); }
void update(int x, i64 k) {
    for (int i = x; i <= n; i += i & -i) bit[i] += k;
}
i64 query(int x) {
    i64 ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += bit[i];
    return ret;
}
i64 query(int l, int r) { return query(r) - query(l - 1); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], update(i, a[i]);
    for (int i = 1; i <= n + 1; i++) fa[i] = i;
    cin >> m;
    for (int i = 1, op, l, r; i <= m; i++) {
        cin >> op >> l >> r;
        if (l > r) swap(l, r);
        if (op) cout << query(l, r) << '\n';
        else
            for (int j = l; j <= r; j = find(j + 1)) {
                update(j, -a[j]);
                update(j, (a[j] = sqrt(a[j])));
                if (a[j] <= 1) fa[j] = j + 1;
            }
    }
    return 0;
}