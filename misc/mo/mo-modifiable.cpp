#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m, l = 1, r, t, a[N], bel[N], cnt[N], siz, c1, c2, ans;
struct query {
    int x, y, t, id, ans;
} q[N], p[N];
bool cmp1(query x, query y) {
    if (bel[x.x] != bel[y.x]) return x.x < y.x;
    if (bel[x.y] != bel[y.y]) return x.y < y.y;
    return x.t < y.t;
}
bool cmp2(query x, query y) { return x.id < y.id; }
void build() {
    siz = pow(n, 0.667);
    for (int i = 1; i <= n; i++) bel[i] = (i - 1) / siz + 1;
}
void insert(int x) { ans += !cnt[a[x]]++; }
void remove(int x) { ans -= !--cnt[a[x]]; }
void update(int x) {
    if (l <= p[x].x && p[x].x <= r) remove(p[x].x);
    swap(a[p[x].x], p[x].y);
    if (l <= p[x].x && p[x].x <= r) insert(p[x].x);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1, x, y; i <= m; i++) {
        char op;
        cin >> op >> x >> y;
        if (op == 'Q') q[++c1] = {x, y, c2, c1};
        else p[++c2] = {x, y, c2, c1};
    }
    build();
    sort(q + 1, q + c1 + 1, cmp1);
    for (int i = 1; i <= c1; i++) {
        while (l > q[i].x) insert(--l);
        while (r < q[i].y) insert(++r);
        while (l < q[i].x) remove(l++);
        while (r > q[i].y) remove(r--);
        while (t < q[i].t) update(++t);
        while (t > q[i].t) update(t--);
        q[i].ans = ans;
    }
    sort(q + 1, q + c1 + 1, cmp2);
    for (int i = 1; i <= c1; i++) cout << q[i].ans << '\n';
    return 0;
}