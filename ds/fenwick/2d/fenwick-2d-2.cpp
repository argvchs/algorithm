#include <iostream>
using namespace std;
const int N = 3e3 + 5;
int n, m, q, t[N][N];
void update(int x, int y, int k) {
    for (int i = x; i <= n; i += i & -i)
        for (int j = y; j <= n; j += j & -j) t[i][j] += k;
}
void update(int x, int y, int z, int w, int k) {
    update(x, y, k);
    update(x, w + 1, -k);
    update(z + 1, y, -k);
    update(z + 1, w + 1, k);
}
int query(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i)
        for (int j = y; j >= 1; j -= j & -j) ret += t[i][j];
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    for (int i = 1, op, x, y, z, w, k; i <= q; i++) {
        cin >> op >> x >> y;
        if (op == 1) cin >> z >> w >> k, update(x, y, z, w, k);
        else cout << query(x, y) << '\n';
    }
}