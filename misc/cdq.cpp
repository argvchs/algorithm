#include <algorithm>
#include <iostream>
#include <tuple>
using namespace std;
const int N = 2e5 + 5;
int n, m, t[N], ans[N];
struct node {
    int a, b, c, cnt, ans;
} a[N], b[N];
bool cmp1(node x, node y) { return tie(x.a, x.b, x.c) < tie(y.a, y.b, y.c); }
bool cmp2(node x, node y) { return tie(x.b, x.c, x.a) < tie(y.b, y.c, y.a); }
bool operator==(node x, node y) { return !cmp1(x, y) && !cmp1(y, x); }
void update(int x, int k) {
    for (int i = x; i <= m; i += i & -i) t[i] += k;
}
int query(int x) {
    int ret = 0;
    for (int i = x; i >= 1; i -= i & -i) ret += t[i];
    return ret;
}
void cdq(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid), cdq(mid + 1, r);
    sort(a + l, a + r + 1, cmp2);
    for (int i = l; i <= r; i++)
        if (a[i].a <= mid) update(a[i].c, a[i].cnt);
        else a[i].ans += query(a[i].c);
    for (int i = l; i <= r; i++)
        if (a[i].a <= mid) update(a[i].c, -a[i].cnt);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].a >> a[i].b >> a[i].c;
    sort(a + 1, a + n + 1, cmp1);
    for (int i = 1; i <= n; i++) b[i] = a[i];
    int cnt = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1, j = 1; i <= cnt; i++)
        while (j <= n && a[i] == b[j]) ++j, ++a[i].cnt;
    for (int i = 1; i <= cnt; i++) a[i].a = i;
    cdq(1, cnt);
    for (int i = 1; i <= cnt; i++) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
    for (int i = 0; i <= n - 1; i++) cout << ans[i] << '\n';
}