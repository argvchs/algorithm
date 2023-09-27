#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, a[N], st[N][25];
void build() {
    for (int i = 1; i <= n; i++) st[i][0] = a[i];
    for (int j = 1; j <= 20; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int query(int l, int r) {
    int k = __lg(r - l + 1);
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        cout << query(l, r) << '\n';
    }
    return 0;
}