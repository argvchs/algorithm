#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
using namespace std;
using i64 = long long;
const int N = 5e4 + 5;
int n, m, l = 1, r, a[N], bel[N], cnt[N], siz;
i64 ans1[N], ans2[N], now;
struct query {
    int l, r, id;
    bool operator<(const query &x) const {
        if (bel[l] != bel[x.l]) return l < x.l;
        return bel[l] & 1 ? r < x.r : r > x.r;
    }
} q[N];
void insert(int x) { now += cnt[a[x]]++; }
void remove(int x) { now -= --cnt[a[x]]; }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m, siz = n / sqrt(m);
    for (int i = 1; i <= n; i++) cin >> a[i], bel[i] = i / siz;
    for (int i = 1; i <= m; i++) cin >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + m + 1);
    for (int i = 1; i <= m; i++) {
        if (q[i].l == q[i].r) {
            ans1[q[i].id] = 0, ans2[q[i].id] = 1;
            continue;
        }
        while (l > q[i].l) insert(--l);
        while (r < q[i].r) insert(++r);
        while (l < q[i].l) remove(l++);
        while (r > q[i].r) remove(r--);
        i64 x = now, y = (i64)(r - l + 1) * (r - l) >> 1;
        i64 g = gcd(x, y);
        ans1[q[i].id] = x / g, ans2[q[i].id] = y / g;
    }
    for (int i = 1; i <= m; i++) cout << ans1[i] << '/' << ans2[i] << '\n';
}