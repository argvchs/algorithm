#include <iomanip>
#include <iostream>
using namespace std;
using f64 = double;
const int N = 105;
const f64 EPS = 1e-7;
int n;
f64 a[N][N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n + 1; j++) cin >> a[i][j];
    for (int i = 1; i <= n; i++) {
        int r = i;
        for (int j = i; j <= n; j++)
            if (abs(a[j][i]) > abs(a[r][i])) r = j;
        if (i != r) swap(a[i], a[r]);
        if (abs(a[i][i]) < EPS) return cout << "No Solution", 0;
        for (int j = 1; j <= n; j++) {
            if (i == j) continue;
            f64 x = a[j][i] / a[i][i];
            for (int k = i; k <= n + 1; k++) a[j][k] -= a[i][k] * x;
        }
    }
    cout << fixed << setprecision(2);
    for (int i = 1; i <= n; i++) cout << a[i][n + 1] / a[i][i] << '\n';
}