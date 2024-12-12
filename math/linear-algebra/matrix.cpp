#include <cstring>
#include <iostream>
using namespace std;
using i64 = long long;
const int N = 105, P = 1e9 + 7;
int n;
i64 m;
struct matrix {
    int a[N][N]{};
    matrix operator*(const matrix &b) const {
        matrix ret;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++) (ret.a[i][j] += (i64)a[i][k] * b.a[k][j] % P) %= P;
        return ret;
    }
} a;
matrix qpow(matrix a, i64 b) {
    matrix ret;
    for (int i = 1; i <= n; i++) ret.a[i][i] = 1;
    for (; b; b >>= 1, a = a * a)
        if (b & 1) ret = ret * a;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a.a[i][j];
    a = qpow(a, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << a.a[i][j] << ' ';
        cout << '\n';
    }
}