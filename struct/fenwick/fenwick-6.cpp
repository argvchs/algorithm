#include <iostream>
using namespace std;
const int N = 3e3 + 5;
int n, m, q, bit1[N][N], bit2[N][N], bit3[N][N], bit4[N][N];
int lowbit(int x) { return x & -x; }
void update(int x, int y, int k) {
    for (int i = x; i <= n; i += lowbit(i))
        for (int j = y; j <= n; j += lowbit(j))
            bit1[i][j] += k, bit2[i][j] += k * x, bit3[i][j] += k * y, bit4[i][j] += k * x * y;
}
void update(int x, int y, int z, int t, int k) {
    update(x, y, k);
    update(x, t + 1, -k);
    update(z + 1, y, -k);
    update(z + 1, t + 1, k);
}
int query(int x, int y) {
    int res = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        for (int j = y; j >= 1; j -= lowbit(j))
            res += (x + 1) * (y + 1) * bit1[i][j] - (y + 1) * bit2[i][j] - (x + 1) * bit3[i][j] +
                   bit4[i][j];
    return res;
}
int query(int x, int y, int z, int t) {
    return query(z, t) - query(x - 1, t) - query(z, y - 1) + query(x - 1, y - 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, op, x, y, z, t, k; i <= q; i++) {
        cin >> op >> x >> y >> z >> t;
        if (op == 1) {
            cin >> k;
            update(x, y, z, t, k);
        } else cout << query(x, y, z, t) << '\n';
    }
    return 0;
}