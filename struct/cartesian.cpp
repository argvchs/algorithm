#include <iostream>
#include <stack>
using namespace std;
using i64 = long long;
const int N = 1e7 + 5;
int n, a[N], l[N], r[N];
i64 ans1, ans2;
stack<int> S;
void build() {
    int pre = 0;
    for (int i = 1; i <= n; i++) {
        while (!S.empty()) {
            if (a[S.top()] < a[i]) break;
            pre = S.top(), S.pop();
        }
        if (!S.empty()) r[S.top()] = i;
        l[i] = pre, pre = 0;
        S.push(i);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build();
    for (int i = 1; i <= n; i++) {
        ans1 ^= (i64)i * (l[i] + 1);
        ans2 ^= (i64)i * (r[i] + 1);
    }
    cout << ans1 << ' ' << ans2;
    return 0;
}