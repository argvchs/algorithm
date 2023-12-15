#include <cmath>
#include <iostream>
using namespace std;
const int N = 2e5 + 5, M = 505;
int n, m, a[N], f[M][M], siz;
char op;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m, siz = sqrt(n);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= siz; j++) f[j][i % j] += a[i];
    for (int i = 1, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 'A') {
            if (x <= siz) cout << f[x][y] << '\n';
            else {
                int ans = 0;
                for (int j = y; j <= n; j += x) ans += a[j];
                cout << ans << '\n';
            }
        } else {
            for (int j = 1; j <= siz; j++) f[j][x % j] += y - a[x];
            a[x] = y;
        }
    }
    return 0;
}