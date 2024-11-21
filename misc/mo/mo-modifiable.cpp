#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, l = 1, r, t, a[N], bel[N], cnt[N], ans[N], siz, qcnt, ccnt, now;
struct query {
    int l, r, t, id;
    bool operator<(const query &x) const {
        if (bel[l] != bel[x.l]) return l < x.l;
        if (bel[r] != bel[x.r]) return bel[l] & 1 ? r < x.r : r > x.r;
        return bel[r] & 1 ? t < x.t : t > x.t;
    }
} q[N];
struct change {
    int x, k;
} c[N];
void insert(int x) { now += !cnt[a[x]]++; }
void remove(int x) { now -= !--cnt[a[x]]; }
void update(int x) {
    if (l <= c[x].x && c[x].x <= r) remove(c[x].x);
    swap(a[c[x].x], c[x].k);
    if (l <= c[x].x && c[x].x <= r) insert(c[x].x);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m, siz = pow(n, 0.667);
    for (int i = 1; i <= n; i++) cin >> a[i], bel[i] = i / siz;
    for (int i = 1, x, y; i <= m; i++) {
        char op;
        cin >> op >> x >> y;
        if (op == 'Q') q[++qcnt] = {x, y, ccnt, qcnt};
        else c[++ccnt] = {x, y};
    }
    sort(q + 1, q + qcnt + 1);
    for (int i = 1; i <= qcnt; i++) {
        while (l > q[i].l) insert(--l);
        while (r < q[i].r) insert(++r);
        while (l < q[i].l) remove(l++);
        while (r > q[i].r) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        ans[q[i].id] = now;
    }
    for (int i = 1; i <= qcnt; i++) cout << ans[i] << '\n';
}