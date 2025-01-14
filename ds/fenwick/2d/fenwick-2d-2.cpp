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
void update(int x, int y, int z, int w, i64 k) {
    update(x, y, k);
    update(x, w + 1, -k);
    update(z + 1, y, -k);
    update(z + 1, w + 1, k);
}
i64 query(int x, int y) {
    i64 ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) ret += t[i][j];
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int op, x, y, z, w, k; cin >> op >> x >> y;)
        if (op == 1) cin >> z >> w >> k, update(x, y, z, w, k);
        else cout << query(x, y) << '\n';
}