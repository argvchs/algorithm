#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, bit1[N], bit2[N];
int lowbit(int x) { return x & -x; }
void update(int x, int k) {
    for (int i = x; i <= n; i += lowbit(i)) bit1[i] += k, bit2[i] += k * x;
}
void update(int x, int y, int k) {
    update(x, k);
    update(y + 1, -k);
}
int query(int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= lowbit(i)) res += (x + 1) * bit1[i] - bit2[i];
    return res;
}
int query(int x, int y) { return query(y) - query(x - 1); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) cin >> x, update(i, i, x);
    for (int i = 1, op, x, y, k; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 1) {
            cin >> k;
            update(x, y, k);
        } else cout << query(x, y) << '\n';
    }
    return 0;
}