#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, bit[N];
void update(int x, int k) {
    for (int i = x; i <= n; i += i & -i) bit[i] += k;
}
int query(int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= i & -i) res += bit[i];
    return res;
}
int query(int x, int y) { return query(y) - query(x - 1); }
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