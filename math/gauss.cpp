#include <iomanip>
#include <iostream>
using namespace std;
using f64 = double;
const int N = 105;
const f64 EPS = 1e-7;
int n;
f64 a[N][N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) {
        int cur = i;
        for (int j = i + 1; j <= n; j++)
            if (abs(a[cur][i]) < abs(a[j][i])) cur = j;
        swap(a[cur], a[i]);
        if (abs(a[i][i]) < EPS) return cout << "No Solution", 0;
        f64 y = a[i][i];
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            f64 x = a[j][i] / y;
            for (int k = i; k <= n + 1; k++) a[j][k] -= x * a[i][k];
        }
        for (int j = 1; j <= n + 1; j++) a[i][j] /= y;
    }
    cout << fixed << setprecision(2);
    for (int i = 1; i <= n; i++) cout << a[i][n + 1] << '\n';
    return 0;
}