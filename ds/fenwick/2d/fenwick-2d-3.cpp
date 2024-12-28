#include <iostream>
using namespace std;
using i64 = long long;
const int N = 5e3 + 5;
int n, m;
i64 t1[N][N], t2[N][N], t3[N][N], t4[N][N];
void update(int x, int y, i64 k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j) {
            t1[i][j] += k;
            t2[i][j] += k * x;
            t3[i][j] += k * y;
            t4[i][j] += k * x * y;
        }
}
void update(int x, int y, int z, int w, i64 k) {
    update(x, y, k);
    update(x, w + 1, -k);
    update(z + 1, y, -k);
    update(z + 1, w + 1, k);
}
i64 query(int x, int y) {
    i64 ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) {
            ret += (x + 1) * (y + 1) * t1[i][j];
            ret -= (y + 1) * t2[i][j];
            ret -= (x + 1) * t3[i][j];
            ret += t4[i][j];
        }
    return ret;
}
i64 query(int x, int y, int z, int w) {
    return query(z, w) - query(x - 1, w) - query(z, y - 1) + query(x - 1, y - 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int op, x, y, z, w, k; cin >> op >> x >> y >> z >> w;)
        if (op == 1) cin >> k, update(x, y, z, w, k);
        else cout << query(x, y, z, w) << '\n';
}