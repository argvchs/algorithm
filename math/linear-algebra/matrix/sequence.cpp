#include <cstring>
#include <iostream>
using namespace std;
using i64 = long long;
const int P = 1e9 + 7;
int n, t;
struct matrix {
    int a[5][5];
} a, b;
matrix operator*(matrix a, matrix b) {
    matrix ret;
    memset(ret.a, 0, sizeof(ret.a));
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                ret.a[i][j] = (ret.a[i][j] + (i64)a.a[i][k] * b.a[k][j]) % P;
    return ret;
}
matrix quickpow(matrix a, int b) {
    matrix ret;
    memset(ret.a, 0, sizeof(ret.a));
    for (int i = 1; i <= 3; i++) ret.a[i][i] = 1;
    for (int i = b; i; i >>= 1, a = a * a)
        if (i & 1) ret = ret * a;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        a.a[1][2] = a.a[2][3] = a.a[3][1] = a.a[3][3] = 1;
        b.a[1][1] = b.a[2][1] = b.a[3][1] = 1;
        cout << (quickpow(a, n - 1) * b).a[1][1] << '\n';
    }
    return 0;
}