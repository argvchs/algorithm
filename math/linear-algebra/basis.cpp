#include <iostream>
using namespace std;
using i64 = long long;
int n;
i64 a, p[65], ret;
void insert(i64 x) {
    for (int i = 60; i >= 0; i--)
        if (x & (1ll << i)) {
            if (p[i]) x ^= p[i];
            else return void(p[i] = x);
        }
}
i64 query() {
    i64 ret = 0;
    for (int i = 60; i >= 0; i--)
        if ((ret ^ p[i]) > ret) ret ^= p[i];
    return ret;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a, insert(a);
    cout << query();
    return 0;
}