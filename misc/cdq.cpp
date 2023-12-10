#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, m, t[N], ans[N];
struct node {
    int a, b, c, cnt, ans;
} a[N], b[N];
bool cmp1(node x, node y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}
bool cmp2(node x, node y) {
    if (x.b != y.b) return x.b < y.b;
    if (x.c != y.c) return x.c < y.c;
    return x.a < y.a;
}
bool cmp3(node x, node y) { return x.a == y.a && x.b == y.b && x.c == y.c; }
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].a >> a[i].b >> a[i].c;
    sort(a + 1, a + n + 1, cmp1);
    for (int i = 1; i <= n; i++) b[i] = a[i];
    int cnt = unique(a + 1, a + n + 1, cmp3) - a - 1;
    for (int i = 1, j = 1; i <= cnt; i++)
        while (j <= n && cmp3(a[i], b[j])) ++j, ++a[i].cnt;
    for (int i = 1; i <= cnt; i++) a[i].a = i;
    cdq(1, cnt);
    for (int i = 1; i <= cnt; i++) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
    for (int i = 1; i <= n; i++) cout << ans[i - 1] << '\n';
    return 0;
}