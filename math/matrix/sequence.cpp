#include <array>
#include <iostream>
using namespace std;
using i64 = long long;
using mat = array<array<int, 5>, 5>;
const int P = 1e9 + 7;
int n, t;
mat a, b, ans;
mat operator*(mat a, mat b) {
    mat ret;
    mat().swap(ret);
    for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
            for (int k = 1; k <= 3; k++)
                ret[i][j] = (ret[i][j] + (i64)a[i][k] * b[k][j]) % P;
    return ret;
}
mat quickpow(mat a, int b) {
    mat ret;
    mat().swap(ret);
    for (int i = 1; i <= 3; i++) ret[i][i] = 1;
    for (int i = b; i; i >>= 1, a = a * a)
        if (i & 1) ret = ret * a;
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        mat().swap(a);
        mat().swap(b);
        cin >> n;
        a[1][2] = a[2][3] = a[3][1] = a[3][3] = 1;
        b[1][1] = b[2][1] = b[3][1] = 1;
        ans = quickpow(a, n - 1) * b;
        cout << ans[1][1] << '\n';
    }
    return 0;
}