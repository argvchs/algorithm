#include <algorithm>
#include <cmath>
#include <iostream>
#include <tuple>
using namespace std;
const int N = 1e5 + 5;
int n, m, l = 1, r, t, a[N], b[N], bel[N], val[N], sum[N], ans[N], siz, bcnt, qcnt, ccnt;
struct query {
    int op, l, r, k, t, id;
} q[N];
struct change {
    int x, k;
} c[N];
bool operator<(query x, query y) {
    return tie(bel[x.l], bel[x.r], x.t) < tie(bel[y.l], bel[y.r], y.t);
}
void build1() {
    siz = pow(n, 0.667);
    for (int i = 1; i <= n; i++) bel[i] = (i - 1) / siz + 1;
}
void build2() {
    siz = sqrt(bcnt);
    for (int i = 1; i <= bcnt; i++) bel[i] = (i - 1) / siz + 1;
}
void insert(int x) { ++val[a[x]], ++sum[bel[a[x]]]; }
void remove(int x) { --val[a[x]], --sum[bel[a[x]]]; }
void update(int x) {
    if (l <= c[x].x && c[x].x <= r) remove(c[x].x);
    swap(a[c[x].x], c[x].k);
    if (l <= c[x].x && c[x].x <= r) insert(c[x].x);
}
int queryrnk(int x) {
    int ret = 0;
    for (int i = 1; i <= bel[x] - 1; i++) ret += sum[i];
    for (int i = x - 1; bel[i] == bel[x]; i--) ret += val[i];
    return ret + 1;
}
int querykth(int x) {
    if (x < 1) return bcnt + 1;
    if (x > r - l + 1) return bcnt + 2;
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
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], b[++bcnt] = a[i];
    for (int i = 1, op, x, y, k; i <= m; i++) {
        cin >> op >> x >> y;
        if (op == 3) c[++ccnt] = {x, k = y};
        else cin >> k, q[++qcnt] = {op, x, y, k, ccnt, qcnt};
        if (op != 2) b[++bcnt] = k;
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
    sort(q + 1, q + qcnt + 1);
    build2();
    for (int i = 1; i <= qcnt; i++) {
        while (l > q[i].l) insert(--l);
        while (r < q[i].r) insert(++r);
        while (l < q[i].l) remove(l++);
        while (r > q[i].r) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        if (q[i].op == 1) ans[q[i].id] = queryrnk(q[i].k);
        else if (q[i].op == 2) ans[q[i].id] = b[querykth(q[i].k)];
        else if (q[i].op == 4) ans[q[i].id] = b[querypre(q[i].k)];
        else ans[q[i].id] = b[querynxt(q[i].k)];
    }
    for (int i = 1; i <= qcnt; i++) cout << ans[i] << '\n';
}