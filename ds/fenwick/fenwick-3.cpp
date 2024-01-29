#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, t1[N], t2[N];
void update(int x, int k) {
    for (int i = x; i <= n; i += i & -i) t1[i] += k, t2[i] += k * x;
}
void update(int l, int r, int k) { update(l, k), update(r + 1, -k); }
int query(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += (x + 1) * t1[i] - t2[i];
    return ret;
}
int query(int l, int r) { return query(r) - query(l - 1); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, update(i, i, x);
    for (int i = 1, op, x, y, k; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 1) cin >> k, update(x, y, k);
        else cout << query(x, y) << '\n';
    }
}