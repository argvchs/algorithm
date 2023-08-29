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
matrix multiply(matrix a, matrix b) {
    matrix res;
    memset(res.a, 0, sizeof(res.a));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                res.a[i][j] = (res.a[i][j] + (i64)a.a[i][k] * b.a[k][j]) % P;
    return res;
}
matrix quickpow(matrix a, i64 b) {
    matrix res;
    memset(res.a, 0, sizeof(res.a));
    for (int i = 1; i <= n; i++) res.a[i][i] = 1;
    while (b) {
        if (b & 1) res = multiply(res, a);
        a = multiply(a, a), b >>= 1;
    }
    return res;
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