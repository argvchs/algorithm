#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
using namespace std;
using i64 = long long;
const int N = 5e4 + 5;
int n, m, l = 1, r, a[N], bel[N], cnt[N], siz;
i64 ans;
struct query {
    int l, r, id;
    i64 ans;
} q[N];
bool cmp1(query x, query y) {
    if (bel[x.l] != bel[y.l]) return x.l < y.l;
    return x.r < y.r;
}
bool cmp2(query x, query y) { return x.id < y.id; }
void build() {
    siz = n / sqrt(m);
    for (int i = 1; i <= n; i++) bel[i] = (i - 1) / siz + 1;
}
void insert(int x) { ans += cnt[a[x]]++; }
void remove(int x) { ans -= --cnt[a[x]]; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r, q[i].id = i;
    build();
    sort(q + 1, q + m + 1, cmp1);
    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) insert(--l);
        while (r < q[i].r) insert(++r);
        while (l < q[i].l) remove(l++);
        while (r > q[i].r) remove(r--);
        q[i].ans = ans;
    }
    sort(q + 1, q + m + 1, cmp2);
    for (int i = 1; i <= m; i++)
        if (q[i].l == q[i].r) cout << "0/1\n";
        else {
            int k = q[i].r - q[i].l + 1;
            i64 x = q[i].ans, y = (i64)k * (k - 1) >> 1, g = gcd(x, y);
            cout << x / g << '/' << y / g << '\n';
        }
    return 0;
}