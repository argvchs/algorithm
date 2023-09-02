#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, m1, m2, l = 1, r, t, a[N], belong[N], cnt[N], siz, ans;
struct node {
    int l, r, x, k, t, id, ans;
} q[N], u[N];
bool cmp1(node a, node b) {
    if (belong[a.l] != belong[b.l]) return a.l < b.l;
    if (belong[a.r] != belong[b.r]) return a.r < b.r;
    return a.t < b.t;
}
bool cmp2(node a, node b) { return a.id < b.id; }
void build() {
    siz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
}
void insert(int x) { ans += !cnt[a[x]]++; }
void remove(int x) { ans -= !--cnt[a[x]]; }
void update(int x) {
    if (l <= u[x].x && u[x].x <= r) remove(u[x].x);
    swap(a[u[x].x], u[x].k);
    if (l <= u[x].x && u[x].x <= r) insert(u[x].x);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    char op;
    for (int i = 1, l, r, x, k; i <= m; i++) {
        cin >> op;
        if (op == 'Q') {
            cin >> l >> r;
            q[++m1] = {l, r, 0, 0, m2, m1};
        } else {
            cin >> x >> k;
            u[++m2] = {0, 0, x, k, m2, m1};
        }
    }
    build();
    sort(q + 1, q + m1 + 1, cmp1);
    for (int i = 1; i <= m1; i++) {
        while (l > q[i].l) insert(--l);
        while (r < q[i].r) insert(++r);
        while (l < q[i].l) remove(l++);
        while (r > q[i].r) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        q[i].ans = ans;
    }
    sort(q + 1, q + m1 + 1, cmp2);
    for (int i = 1; i <= m1; i++) cout << q[i].ans << '\n';
    return 0;
}