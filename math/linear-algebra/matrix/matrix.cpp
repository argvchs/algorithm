#include <iostream>
using namespace std;
using i64 = long long;
const int N = 105, P = 1e9 + 7;
i64 n, m;
struct mat {
    int a[N][N]{};
} a, ans;
mat operator*(mat a, mat b) {
    mat ret;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                ret.a[i][j] = (ret.a[i][j] + (i64)a.a[i][k] * b.a[k][j]) % P;
    return ret;
}
mat quickpow(mat a, i64 b) {
    mat ret;
    for (int i = 1; i <= n; i++) ret.a[i][i] = 1;
    for (i64 i = b; i; i >>= 1, a = a * a)
        if (i & 1) ret = ret * a;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) cin >> a.a[i][j];
    ans = quickpow(a, m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cout << ans.a[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}