#include <cstring>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 105, P = 1e9 + 7;
int n;
i64 m;
struct matrix {
    i64 a[N][N];
} a;
matrix quickmul(matrix a, matrix b) {
    matrix ret;
    memset(ret.a, 0, sizeof(ret.a));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                ret.a[i][j] = (ret.a[i][j] + (i64)a.a[i][k] * b.a[k][j]) % P;
    return ret;
}
matrix quickpow(matrix a, i64 b) {
    matrix ret;
    memset(ret.a, 0, sizeof(ret.a));
    for (int i = 1; i <= n; i++) ret.a[i][i] = 1;
    for (int i = b; i; i >>= 1, a = quickmul(a, a))
        if (i & 1) ret = quickmul(ret, a);
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a.a[i][j];
    a = quickpow(a, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << a.a[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}