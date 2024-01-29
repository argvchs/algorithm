#include <algorithm>
#include <bit>
#include <iostream>
using namespace std;
using u32 = unsigned;
const int N = 1e5 + 5;
int n, m, a[N], f[N][25];
int query(int l, int r) {
    int k = bit_width<u32>(r - l + 1) - 1;
    return max(f[l][k], f[r - (1 << k) + 1][k]);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> f[i][0];
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
}