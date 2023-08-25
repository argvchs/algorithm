#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, m1, m2, l = 1, r, t, a[N], belong[N], cnt[N], siz, ans;
struct node {
    int l, r, x, k, t, id, ans;
} q[N], u[N];
bool comp1(node a, node b) {
    if (belong[a.l] != belong[b.l]) return a.l < b.l;
    if (belong[a.r] != belong[b.r]) return a.r < b.r;
    return a.t < b.t;
}
bool comp2(node a, node b) { return a.id < b.id; }
void build() {
    siz = pow(n, 2.0 / 3.0);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
}
void insert(int x) { ans += !cnt[x]++; }
void remove(int x) { ans -= !--cnt[x]; }
void update(int x, int &k) {
    if (l <= x && x <= r) remove(a[x]), insert(k);
    swap(a[x], k);
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
    sort(q + 1, q + m1 + 1, comp1);
    for (int i = 1; i <= m1; i++) {
        while (l > q[i].l) insert(a[--l]);
        while (r < q[i].r) insert(a[++r]);
        while (l < q[i].l) remove(a[l++]);
        while (r > q[i].r) remove(a[r--]);
        while (t < q[i].t) ++t, update(u[t].x, u[t].k);
        while (t > q[i].t) update(u[t].x, u[t].k), --t;
        q[i].ans = ans;
    }
    sort(q + 1, q + m1 + 1, comp2);
    for (int i = 1; i <= m1; i++) cout << q[i].ans << '\n';
    return 0;
}