#include <iostream>
using namespace std;
using i64 = long long;
const int N = 1e6 + 5;
int n, q;
i64 t[N];
void update(int x, i64 k) {
    for (int i = x; i <= n; i += i & -i) t[i] += k;
}
void update(int l, int r, i64 k) { update(l, k), update(r + 1, -k); }
i64 query(int x) {
    i64 ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += t[i];
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1, x; i <= n; i++) cin >> x, update(i, i, x);
    for (int i = 1, op, x, y, k; i <= q; i++) {
        cin >> op >> x;
        if (op == 1) cin >> y >> k, update(x, y, k);
        else cout << query(x) << '\n';
    }
}