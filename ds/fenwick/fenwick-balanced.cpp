#include <algorithm>
#include <iostream>
using namespace std;
constexpr int N = 1e5 + 5;
int n, a[N], b[N], op[N], bit[N], cnt;
void update(int x, int k) {
    for (int i = x; i <= cnt; i += i & -i) bit[i] += k;
}
int query(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += bit[i];
    return ret;
}
int queryrnk(int x) { return query(x - 1) + 1; }
int querykth(int x) {
    int ret = 0;
    for (int i = 20; i >= 1; i--)
        if ((ret += (1 << (i - 1))) <= cnt && x > bit[ret]) x -= bit[ret];
        else ret -= (1 << (i - 1));
    return ret + 1;
}
int querypre(int x) { return querykth(queryrnk(x) - 1); }
int querynex(int x) { return querykth(queryrnk(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> op[i] >> a[i];
        if (op[i] != 4) b[++cnt] = a[i];
    }
    sort(b + 1, b + cnt + 1);
    cnt = unique(b + 1, b + cnt + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        if (op[i] != 4) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
    for (int i = 1; i <= n; i++)
        if (op[i] == 1) update(a[i], 1);
        else if (op[i] == 2) update(a[i], -1);
        else if (op[i] == 3) cout << queryrnk(a[i]) << '\n';
        else if (op[i] == 4) cout << b[querykth(a[i])] << '\n';
        else if (op[i] == 5) cout << b[querypre(a[i])] << '\n';
        else cout << b[querynex(a[i])] << '\n';
    return 0;
}