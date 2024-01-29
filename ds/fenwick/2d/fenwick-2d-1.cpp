#include <iostream>
using namespace std;
const int N = 3e3 + 5;
int n, m, q, t[N][N];
void update(int x, int y, int k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j) t[i][j] += k;
}
int query(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) ret += t[i][j];
    return ret;
}
int query(int x, int y, int z, int w) {
    return query(z, w) - query(x - 1, w) - query(z, y - 1) + query(x - 1, y - 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, op, x, y, z, w; i <= q; i++) {
        cin >> op >> x >> y >> z;
        if (op == 1) update(x, y, z);
        else cin >> w, cout << query(x, y, z, w) << '\n';
    }
}