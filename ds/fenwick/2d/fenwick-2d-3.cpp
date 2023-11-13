#include <iostream>
using namespace std;
const int N = 3e3 + 5;
int n, m, q, t1[N][N], t2[N][N], t3[N][N], t4[N][N];
void update(int x, int y, int k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j) {
            t1[i][j] += k;
            t2[i][j] += k * x;
            t3[i][j] += k * y;
            t4[i][j] += k * x * y;
        }
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
        for (int j = y; j >= 1; j -= j & -j) {
            ret += (x + 1) * (y + 1) * t1[i][j];
            ret -= (y + 1) * t2[i][j];
            ret -= (x + 1) * t3[i][j];
            ret += t4[i][j];
        }
    return ret;
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
        if (op == 1) cin >> k, update(x, y, z, t, k);
        else cout << query(x, y, z, t) << '\n';
    }
    return 0;
}