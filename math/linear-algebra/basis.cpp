#include <iostream>
using namespace std;
using i64 = long long;
int n;
i64 a, p[65];
void insert(i64 x) {
    for (int i = 60; i >= 0; i--) {
        if (!(x & (1ll << i))) continue;
        if (!p[i]) return void(p[i] = x);
        x ^= p[i];
    }
}
i64 query() {
    i64 ret = 0;
    for (int i = 60; i >= 0; i--)
        if ((ret ^ p[i]) > ret) ret ^= p[i];
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a, insert(a);
    cout << query();
}