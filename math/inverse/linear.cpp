#include <iostream>
#include <tuple>
using namespace std;
using i64 = long long;
const int N = 3e6 + 5;
int n, p, inv[N];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (i64)(p - p / i) * inv[p % i] % p;
    for (int i = 1; i <= n; i++) cout << inv[i] << '\n';
    return 0;
}