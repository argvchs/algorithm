#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, t, a[N], b[N], cnt;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
        sort(b + 1, b + n + 1);
        int cnt = unique(b + 1, b + n + 1) - b - 1;
        for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
        for (int i = 1; i <= n; i++) cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}