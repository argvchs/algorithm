#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
using namespace std;
const int N = 1e5 + 5;
int n, m, m1, m2, l = 1, r, t, a[N], b[N], belong[N], val[N], sum[N], siz, cnt;
struct node {
    int op, x, y, k, t, id, ans;
} q[N], u[N];
auto cmp1 = [](node a, node b) {
    if (belong[a.x] != belong[b.x]) return a.x < b.x;
    if (belong[a.y] != belong[b.y]) return a.y < b.y;
    return a.t < b.t;
};
auto cmp2 = [](node a, node b) { return a.id < b.id; };
void build1() {
    siz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
}
void build2() {
    siz = sqrt(cnt);
    for (int i = 1; i <= cnt; i++) belong[i] = (i - 1) / siz + 1;
}
void insert(int x) { ++val[a[x]], ++sum[belong[a[x]]]; }
void remove(int x) { --val[a[x]], --sum[belong[a[x]]]; }
void update(int x) {
    if (l <= u[x].x && u[x].x <= r) remove(u[x].x);
    swap(a[u[x].x], u[x].k);
    if (l <= u[x].x && u[x].x <= r) insert(u[x].x);
}
int queryrank(int x) {
    int ret = 0;
    for (int i = 1; i <= belong[x] - 1; i++) ret += sum[i];
    for (int i = x - 1; belong[i] == belong[x]; i--) ret += val[i];
    return ret + 1;
}
int querykth(int x) {
    if (x < 1) return cnt + 1;
    if (x > r - l + 1) return cnt + 2;
    int ret1 = 1, ret2 = 1, cur = 0;
    while (cur + sum[ret1] < x) cur += sum[ret1++], ret2 += siz;
    while (cur + val[ret2] < x) cur += val[ret2++];
    return ret2;
}
int querypre(int x) { return querykth(queryrank(x) - 1); }
int querynext(int x) { return querykth(queryrank(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m, cnt = n;
    for (int i = 1; i <= n; i++) cin >> a[i], b[i] = a[i];
    for (int i = 1, op, x, y, k; i <= m; i++) {
        cin >> op >> x;
        if (op == 3) cin >> k, u[++m2] = {op, x, 0, k, m2, m1};
        else cin >> y >> k, q[++m1] = {op, x, y, k, m2, m1};
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
    sort(q + 1, q + m1 + 1, cmp1);
    build2();
    for (int i = 1; i <= m1; i++) {
        while (l > q[i].x) insert(--l);
        while (r < q[i].y) insert(++r);
        while (l < q[i].x) remove(l++);
        while (r > q[i].y) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        if (q[i].op == 1) q[i].ans = queryrank(q[i].k);
        else if (q[i].op == 2) q[i].ans = b[querykth(q[i].k)];
        else if (q[i].op == 4) q[i].ans = b[querypre(q[i].k)];
        else q[i].ans = b[querynext(q[i].k)];
    }
    sort(q + 1, q + m1 + 1, cmp2);
    for (int i = 1; i <= m1; i++) cout << q[i].ans << '\n';
    return 0;
}