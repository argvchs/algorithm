#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, m, l = 1, r, t, a[N], b[N], bel[N], val[N], sum[N], ans[N], siz, bcnt, qcnt, ucnt;
struct query {
    int op, l, r, k, t, id;
    bool operator<(const query &x) const {
        if (bel[l] != bel[x.l]) return l < x.l;
        if (bel[r] != bel[x.r]) return bel[l] & 1 ? r < x.r : r > x.r;
        return bel[r] & 1 ? t < x.t : t > x.t;
    }
} q[N];
struct update {
    int x, k;
} u[N];
void insert(int x) { ++val[a[x]], ++sum[bel[a[x]]]; }
void remove(int x) { --val[a[x]], --sum[bel[a[x]]]; }
void update(int x) {
    if (l <= u[x].x && u[x].x <= r) remove(u[x].x);
    swap(a[u[x].x], u[x].k);
    if (l <= u[x].x && u[x].x <= r) insert(u[x].x);
}
int queryrnk(int x) {
    int ret = 0;
    for (int i = 1; i <= bel[x] - 1; i++) ret += sum[i];
    for (int i = x - 1; bel[i] == bel[x]; i--) ret += val[i];
    return ret + 1;
}
int querykth(int x) {
    if (x < 1) return 0x80000001;
    if (x > r - l + 1) return 0x7fffffff;
    int i = 1, j = 1, k = 0;
    while (k + sum[i] < x) k += sum[i++], j += siz;
    while (k + val[j] < x) k += val[j++];
    return b[j];
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
        if (op == 3) u[++ucnt] = {x, k = y};
        else cin >> k, q[++qcnt] = {op, x, y, k, ucnt, qcnt};
        if (op != 2) b[++bcnt] = k;
    }
    sort(b + 1, b + bcnt + 1);
    bcnt = unique(b + 1, b + bcnt + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + bcnt + 1, a[i]) - b;
    for (int i = 1; i <= qcnt; i++)
        if (q[i].op != 2) q[i].k = lower_bound(b + 1, b + bcnt + 1, q[i].k) - b;
    for (int i = 1; i <= ucnt; i++) u[i].k = lower_bound(b + 1, b + bcnt + 1, u[i].k) - b;
    siz = pow(n, 2.0 / 3);
    for (int i = 1; i <= n; i++) bel[i] = i / siz;
    sort(q + 1, q + qcnt + 1);
    siz = sqrt(bcnt);
    for (int i = 1; i <= bcnt; i++) bel[i] = (i - 1) / siz + 1;
    for (int i = 1; i <= qcnt; i++) {
        while (l > q[i].l) insert(--l);
        while (r < q[i].r) insert(++r);
        while (l < q[i].l) remove(l++);
        while (r > q[i].r) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        if (q[i].op == 1) ans[q[i].id] = queryrnk(q[i].k);
        else if (q[i].op == 2) ans[q[i].id] = querykth(q[i].k);
        else if (q[i].op == 4) ans[q[i].id] = querypre(q[i].k);
        else ans[q[i].id] = querynxt(q[i].k);
    }
    for (int i = 1; i <= qcnt; i++) cout << ans[i] << '\n';
}