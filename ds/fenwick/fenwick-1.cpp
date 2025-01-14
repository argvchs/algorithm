#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e6 + 5;
int n, q;
i64 t[N];
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
    cin >> n >> q;
    for (int i = 1, x; i <= n; i++) cin >> x, update(i, x);
    for (int i = 1, op, x, y; i <= q; i++) {
        cin >> op >> x >> y;
        if (op == 1) update(x, y);
        else cout << query(x, y) << '\n';
    }
}