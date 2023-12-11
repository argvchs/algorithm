#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, l = 1, r, t, a[N], b[N], bel[N], cnt[N], sum[N], siz, c1, c2, c3;
struct query {
    int op, x, y, k, t, id, ans;
} q[N], p[N];
bool cmp1(query x, query y) {
    if (bel[x.x] != bel[y.x]) return x.x < y.x;
    if (bel[x.y] != bel[y.y]) return x.y < y.y;
    return x.t < y.t;
}
bool cmp2(query x, query y) { return x.id < y.id; }
void build1() {
    siz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) bel[i] = (i - 1) / siz + 1;
}
void build2() {
    siz = sqrt(c3);
    for (int i = 1; i <= c3; i++) bel[i] = (i - 1) / siz + 1;
}
void insert(int x) { ++cnt[a[x]], ++sum[bel[a[x]]]; }
void remove(int x) { --cnt[a[x]], --sum[bel[a[x]]]; }
void update(int x) {
    if (l <= p[x].x && p[x].x <= r) remove(p[x].x);
    swap(a[p[x].x], p[x].k);
    if (l <= p[x].x && p[x].x <= r) insert(p[x].x);
}
int queryrnk(int x) {
    int ret = 0;
    for (int i = 1; i <= bel[x] - 1; i++) ret += sum[i];
    for (int i = x - 1; bel[i] == bel[x]; i--) ret += cnt[i];
    return ret + 1;
}
int querykth(int x) {
    if (x < 1) return c3 + 1;
    if (x > r - l + 1) return c3 + 2;
    int i = 1, j = 1, k = 0;
    while (k + sum[i] < x) k += sum[i++], j += siz;
    while (k + cnt[j] < x) k += cnt[j++];
    return j;
}
int querypre(int x) { return querykth(queryrnk(x) - 1); }
int querynxt(int x) { return querykth(queryrnk(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], b[++c3] = a[i];
    for (int i = 1, op, x, y, k; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 3) p[++c2] = {op, x, 0, k = y, c2, c1};
        else cin >> k, q[++c1] = {op, x, y, k, c2, c1};
        if (op != 2) b[++c3] = k;
    }
    sort(b + 1, b + bcnt + 1);
    bcnt = unique(b + 1, b + bcnt + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + bcnt + 1, a[i]) - b;
    for (int i = 1; i <= qcnt; i++)
        if (q[i].op != 2) q[i].k = lower_bound(b + 1, b + bcnt + 1, q[i].k) - b;
    for (int i = 1; i <= ccnt; i++) c[i].k = lower_bound(b + 1, b + bcnt + 1, c[i].k) - b;
    b[bcnt + 1] = 0x80000001;
    b[bcnt + 2] = 0x7fffffff;
    build1();
    sort(q + 1, q + c1 + 1, cmp1);
    build2();
    for (int i = 1; i <= c1; i++) {
        while (l > q[i].x) insert(--l);
        while (r < q[i].y) insert(++r);
        while (l < q[i].x) remove(l++);
        while (r > q[i].y) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        if (q[i].op == 1) q[i].ans = queryrnk(q[i].k);
        else if (q[i].op == 2) q[i].ans = b[querykth(q[i].k)];
        else if (q[i].op == 4) q[i].ans = b[querypre(q[i].k)];
        else q[i].ans = b[querynxt(q[i].k)];
    }
    sort(q + 1, q + c1 + 1, cmp2);
    for (int i = 1; i <= c1; i++) cout << q[i].ans << '\n';
    return 0;
}