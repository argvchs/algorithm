#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], b[N], op[N], bel[N], val[N], sum[N], siz, tot;
void build() {
    siz = sqrt(tot);
    for (int i = 1; i <= tot; i++) bel[i] = (i - 1) / siz + 1;
}
void insert(int x) { ++val[x], ++sum[bel[x]]; }
void remove(int x) { --val[x], --sum[bel[x]]; }
int queryrnk(int x) {
    int ret = 0;
    for (int i = 1; i <= bel[x] - 1; i++) ret += sum[i];
    for (int i = x - 1; bel[i] == bel[x]; i--) ret += val[i];
    return ret + 1;
}
int querykth(int x) {
    int ret1 = 1, ret2 = 1, cur = 0;
    while (cur + sum[ret1] < x) cur += sum[ret1++], ret2 += siz;
    while (cur + val[ret2] < x) cur += val[ret2++];
    return ret2;
}
int querypre(int x) { return querykth(queryrnk(x) - 1); }
int querynex(int x) { return querykth(queryrnk(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> op[i] >> a[i];
        if (op[i] != 4) b[++tot] = a[i];
    }
    sort(b + 1, b + tot + 1);
    tot = unique(b + 1, b + tot + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        if (op[i] != 4) a[i] = lower_bound(b + 1, b + tot + 1, a[i]) - b;
    build();
    for (int i = 1; i <= n; i++)
        if (op[i] == 1) insert(a[i]);
        else if (op[i] == 2) remove(a[i]);
        else if (op[i] == 3) cout << queryrnk(a[i]) << '\n';
        else if (op[i] == 4) cout << b[querykth(a[i])] << '\n';
        else if (op[i] == 5) cout << b[querypre(a[i])] << '\n';
        else cout << b[querynex(a[i])] << '\n';
    return 0;
}