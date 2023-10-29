#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, t[N];
void update(int x, int k) {
    for (int i = x; i <= n; i += i & -i) t[i] += k;
}
void update(int l, int r, int k) { update(l, k), update(r + 1, -k); }
int query(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += t[i];
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        update(i, i, x);
    }
    for (int i = 1, op, x, y, k; i <= m; i++) {
        cin >> op >> x;
        if (op == 1) cin >> y >> k, update(x, y, k);
        else cout << query(x) << '\n';
    }
    return 0;
}