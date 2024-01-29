#include <cmath>
#include <iostream>
#include <utility>
using namespace std;
using i64 = long long;
const int N = 1e5 + 5;
int n, m, fa[N];
i64 a[N], t[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void update(int x, i64 k) {
    for (int i = x; i <= n; i += i & -i) t[i] += k;
}
i64 query(int x) {
    i64 ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += t[i];
    return ret;
}
i64 query(int l, int r) { return query(r) - query(l - 1); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], update(i, a[i]);
    for (int i = 1; i <= n + 1; i++) fa[i] = i;
    cin >> m;
    for (int i = 1, op, l, r; i <= m; i++) {
        cin >> op >> l >> r;
        if (l > r) swap(l, r);
        if (!op)
            for (int j = find(l); j <= r; j = find(j + 1)) {
                update(j, -a[j]);
                update(j, a[j] = sqrt(a[j]));
                if (a[j] <= 1) fa[j] = j + 1;
            }
        else cout << query(l, r) << '\n';
    }
}