#include <algorithm>
#include <iostream>
using namespace std;
const int N = 2e5 + 5;
int n, m, t[N], ans[N];
struct node {
    int a, b, c, cnt, ans;
} a[N], b[N];
bool operator<(node x, node y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}
bool operator==(node x, node y) { return !(x < y || y < x); }
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
    int i = l, j = mid + 1, cnt = 0;
    while (i <= mid && j <= r)
        if (a[i].b <= a[j].b) update(a[i].c, a[i].cnt), b[++cnt] = a[i++];
        else a[j].ans += query(a[j].c), b[++cnt] = a[j++];
    while (i <= mid) update(a[i].c, a[i].cnt), b[++cnt] = a[i++];
    while (j <= r) a[j].ans += query(a[j].c), b[++cnt] = a[j++];
    for (int i = l; i <= mid; i++) update(a[i].c, -a[i].cnt);
    for (int i = 1; i <= cnt; i++) a[i + l - 1] = b[i];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].a >> a[i].b >> a[i].c;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) b[i] = a[i];
    int cnt = unique(a + 1, a + n + 1) - a - 1;
    for (int i = 1, j = 1; i <= cnt; i++)
        while (j <= n && a[i] == b[j]) ++j, ++a[i].cnt;
    cdq(1, cnt);
    for (int i = 1; i <= cnt; i++) ans[a[i].ans + a[i].cnt - 1] += a[i].cnt;
    for (int i = 0; i <= n - 1; i++) cout << ans[i] << '\n';
    return 0;
}