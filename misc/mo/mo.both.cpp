#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;
const int N = 1e5 + 5;
int n, m, m1, m2, l = 1, r, t, a[N], b[N], belong[N], val[N], sum[N], siz, cnt;
struct node {
    int op, l, r, x, k, t, id, ans;
} q[N], u[N];
bool comp1(node a, node b) {
    if (belong[a.l] != belong[b.l]) return a.l < b.l;
    if (belong[a.r] != belong[b.r]) return a.r < b.r;
    return a.t < b.t;
}
bool comp2(node a, node b) { return a.id < b.id; }
void build1() {
    siz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
}
void build2() {
    siz = sqrt(cnt);
    for (int i = 1; i <= cnt; i++) belong[i] = (i - 1) / siz + 1;
}
void insert(int x) { ++val[x], ++sum[belong[x]]; }
void remove(int x) { --val[x], --sum[belong[x]]; }
int queryrank(int x) {
    int res = 0;
    for (int i = 1; i <= belong[x] - 1; i++) res += sum[i];
    for (int i = x - 1; belong[i] == belong[x]; i--) res += val[i];
    return res + 1;
}
int querykth(int x) {
    if (x < 1) return cnt + 1;
    if (x > r - l + 1) return cnt + 2;
    int i = 1, j = 1, k = 0;
    while (k + sum[i] < x) k += sum[i++], j += siz;
    while (k + val[j] < x) k += val[j++];
    return j;
}
int querypre(int x) { return querykth(queryrank(x) - 1); }
int querynext(int x) { return querykth(queryrank(x + 1)); }
void update(int x, int &k) {
    if (l <= x && x <= r) remove(a[x]), insert(k);
    swap(a[x], k);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i], b[++cnt] = a[i];
    for (int i = 1, op, l, r, x, k; i <= m; i++) {
        cin >> op;
        if (op == 3) {
            cin >> x >> k;
            u[++m2] = {op, 0, 0, x, k, m2, m1};
        } else {
            cin >> l >> r >> k;
            q[++m1] = {op, l, r, 0, k, m2, m1};
        }
        if (op != 2) b[++cnt] = k;
    }
    sort(b + 1, b + cnt + 1);
    cnt = unique(b + 1, b + cnt + 1) - b - 1;
    for (int i = 1; i <= n; i++) a[i] = lower_bound(b + 1, b + cnt + 1, a[i]) - b;
    for (int i = 1; i <= m1; i++)
        if (q[i].op != 2) q[i].k = lower_bound(b + 1, b + cnt + 1, q[i].k) - b;
    for (int i = 1; i <= m2; i++)
        if (u[i].op != 2) u[i].k = lower_bound(b + 1, b + cnt + 1, u[i].k) - b;
    b[cnt + 1] = numeric_limits<int>::min() + 1;
    b[cnt + 2] = numeric_limits<int>::max();
    build1();
    sort(q + 1, q + m1 + 1, comp1);
    build2();
    for (int i = 1; i <= m1; i++) {
        while (l > q[i].l) insert(a[--l]);
        while (r < q[i].r) insert(a[++r]);
        while (l < q[i].l) remove(a[l++]);
        while (r > q[i].r) remove(a[r--]);
        while (t < q[i].t) ++t, update(u[t].x, u[t].k);
        while (t > q[i].t) update(u[t].x, u[t].k), --t;
        if (q[i].op == 1) q[i].ans = queryrank(q[i].k);
        else if (q[i].op == 2) q[i].ans = b[querykth(q[i].k)];
        else if (q[i].op == 4) q[i].ans = b[querypre(q[i].k)];
        else if (q[i].op == 5) q[i].ans = b[querynext(q[i].k)];
    }
    sort(q + 1, q + m1 + 1, comp2);
    for (int i = 1; i <= m1; i++) cout << q[i].ans << '\n';
    return 0;
}