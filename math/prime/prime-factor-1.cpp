#include <iostream>
using namespace std;
using i64 = long long;
int t;
i64 n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        for (i64 i = 2; i * i <= n; i++)
            while (!(n % i)) {
                cout << i << ' ';
                n /= i;
            }
        if (n != 1) cout << n;
        cout << '\n';
    }
    return 0;
}