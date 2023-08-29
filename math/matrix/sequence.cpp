#include <cstring>
#include <iostream>
using namespace std;
using i64 = long long;
const int P = 1e9 + 7;
int n, t;
struct matrix {
    int a[5][5];
} a, b;
matrix multiply(matrix a, matrix b) {
    matrix res;
    memset(res.a, 0, sizeof(res.a));
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                res.a[i][j] = (res.a[i][j] + (i64)a.a[i][k] * b.a[k][j]) % P;
    return res;
}
matrix quickpow(matrix a, int b) {
    matrix res;
    memset(res.a, 0, sizeof(res.a));
    for (int i = 1; i <= 3; i++) res.a[i][i] = 1;
    while (b) {
        if (b & 1) res = multiply(res, a);
        a = multiply(a, a), b >>= 1;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        memset(a.a, 0, sizeof(a.a));
        memset(b.a, 0, sizeof(b.a));
        cin >> n;
        a.a[1][2] = a.a[2][3] = a.a[3][1] = a.a[3][3] = 1;
        b.a[1][1] = b.a[2][1] = b.a[3][1] = 1;
        b = multiply(quickpow(a, n - 1), b);
        cout << b.a[1][1] << '\n';
    }
    return 0;
}