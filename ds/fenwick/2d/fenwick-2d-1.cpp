#include <iostream>
using namespace std;
using i64 = long long;
const int N = 5e3 + 5;
int n, m;
i64 t[N][N];
void update(int x, int y, i64 k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= m; j += j & -j) t[i][j] += k;
}
i64 query(int x, int y) {
    i64 ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) ret += t[i][j];
    return ret;
}
i64 query(int x, int y, int z, int w) {
    return query(z, w) - query(x - 1, w) - query(z, y - 1) + query(x - 1, y - 1);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int op, x, y, z, w; cin >> op >> x >> y >> z;)
        if (op == 1) update(x, y, z);
        else cin >> w, cout << query(x, y, z, w) << '\n';
}