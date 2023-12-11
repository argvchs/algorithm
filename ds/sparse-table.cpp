#include <bit>
#include <iostream>
using namespace std;
using u32 = unsigned;
const int N = 1e5 + 5;
int n, m, a[N], f[25][N];
int query(int l, int r) {
    int k = bit_width<u32>(r - l + 1) - 1;
    return max(f[k][l], f[k][r - (1 << k) + 1]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> f[0][i];
    for (int i = 1; i <= 20; i++)
        for (int j = 1; j + (1 << i) - 1 <= n; j++)
            f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
    return 0;
}