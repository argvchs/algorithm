#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], b[N], op[N], bel[N], val[N], sum[N], siz, cnt;
void insert(int x) { ++val[x], ++sum[bel[x]]; }
void remove(int x) { --val[x], --sum[bel[x]]; }
int queryrnk(int x) {
    int ret = 0;
    for (int i = 1; i <= bel[x] - 1; i++) ret += sum[i];
    for (int i = x - 1; bel[i] == bel[x]; i--) ret += val[i];
    return ret + 1;
}
int querykth(int x) {
    int i = 1, j = 1, k = 0;
    while (k + sum[i] < x) k += sum[i++], j += siz;
    while (k + val[j] < x) k += val[j++];
    return j;
}
int querypre(int x) { return querykth(queryrnk(x) - 1); }
int querynxt(int x) { return querykth(queryrnk(x + 1)); }
int main() {
    ios_base::sync_with_stdio(false);
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
    siz = sqrt(cnt);
    for (int i = 1; i <= cnt; i++) bel[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= n; i++)
        if (op[i] == 1) insert(a[i]);
        else if (op[i] == 2) remove(a[i]);
        else if (op[i] == 3) cout << queryrnk(a[i]) << '\n';
        else if (op[i] == 4) cout << b[querykth(a[i])] << '\n';
        else if (op[i] == 5) cout << b[querypre(a[i])] << '\n';
        else cout << b[querynxt(a[i])] << '\n';
}