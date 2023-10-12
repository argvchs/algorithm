#include <iostream>
using namespace std;
constexpr int N = 1e6 + 5;
int n, m, bit[N];
void update(int x, int k) {
    for (int i = x; i <= n; i += i & -i) bit[i] += k;
}
int query(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += bit[i];
    return ret;
}
int query(int l, int r) { return query(r) - query(l - 1); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, update(i, x);
    for (int i = 1, op, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 1) update(x, y);
        else cout << query(x, y) << '\n';
    }
    return 0;
}