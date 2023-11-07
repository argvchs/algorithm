#include <iostream>
using namespace std;
const int N = 3005;
int n, m, q, t[N][N];
void update(int x, int y, int k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j) t[i][j] += k;
}
void update(int x, int y, int z, int t, int k) {
    update(x, y, k);
    update(x, t + 1, -k);
    update(z + 1, y, -k);
    update(z + 1, t + 1, k);
}
int query(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) ret += t[i][j];
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, op, x, y, z, t, k; i <= q; i++) {
        cin >> op >> x >> y;
        if (op == 1) cin >> z >> t >> k, update(x, y, z, t, k);
        else cout << query(x, y) << '\n';
    }
    return 0;
}