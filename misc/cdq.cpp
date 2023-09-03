#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, m, bit[N], ans[N], cnt;
struct node {
    int a, b, c, cnt, ans;
} a[N], b[N];
bool cmp1(node a, node b) {
    if (a.a != b.a) return a.a < b.a;
    if (a.b != b.b) return a.b < b.b;
    return a.c < b.c;
}
bool cmp2(node a, node b) {
    if (a.b != b.b) return a.b < b.b;
    if (a.c != b.c) return a.c < b.c;
    return a.a < b.a;
}
bool cmp3(node a, node b) { return a.a == b.a && a.b == b.b && a.c == b.c; }
void update(int x, int k) {
    for (int i = x; i <= m; i += i & -i) bit[i] += k;
}
int query(int x) {
    int res = 0;
    for (int i = x; i >= 1; i -= i & -i) res += bit[i];
    return res;
}
void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
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
    for (int i = 1; i <= n; i++) cin >> a[i].a >> a[i].b >> a[i].c, b[i] = a[i];
    sort(a + 1, a + n + 1, cmp1);
    sort(b + 1, b + n + 1, cmp1);
    cnt = unique(a + 1, a + n + 1, cmp3) - a - 1;
    for (int i = 1, j = 1; i <= cnt; i++)
        while (j <= n && cmp3(a[i], b[j])) ++j, ++a[i].cnt;
    for (int i = 1; i <= cnt; i++) a[i].a = i;
    solve(1, cnt);
    for (int i = 1; i <= cnt; i++) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
    for (int i = 1; i <= n; i++) cout << ans[i - 1] << '\n';
    return 0;
}