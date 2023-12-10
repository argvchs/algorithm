#include <cstring>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 105, P = 1e9 + 7;
int n;
i64 m;
struct matrix {
    int a[N][N];
} a, ans;
matrix operator*(matrix a, matrix b) {
    matrix ret;
    memset(ret.a, 0, sizeof(ret.a));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                ret.a[i][j] = (ret.a[i][j] + (i64)a.a[i][k] * b.a[k][j]) % P;
    return ret;
}
matrix qpow(matrix a, i64 b) {
    matrix ret;
    memset(ret.a, 0, sizeof(ret.a));
    for (int i = 1; i <= n; i++) ret.a[i][i] = 1;
    for (; b; b >>= 1, a = a * a)
        if (b & 1) ret = ret * a;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a.a[i][j];
    ans = qpow(a, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << ans.a[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}