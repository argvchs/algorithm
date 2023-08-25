#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
using namespace std;
using i64 = long long;
const int N = 5e4 + 5;
int n, m, l = 1, r, a[N], belong[N], cnt[N], siz;
i64 ans;
struct node {
    int l, r, id;
    i64 ans1, ans2;
} q[N];
bool comp1(node a, node b) {
    if (belong[a.l] != belong[b.l]) return a.l < b.l;
    return a.r < b.r;
}
bool comp2(node a, node b) { return a.id < b.id; }
void build() {
    siz = n / sqrt(m);
    for (int i = 1; i <= n; i++) belong[i] = (i - 1) / siz + 1;
}
void insert(int x) { ans += cnt[x]++; }
void remove(int x) { ans -= --cnt[x]; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    build();
    sort(q + 1, q + m + 1, comp1);
    for (int i = 1; i <= m; i++) {
        while (l > q[i].l) insert(a[--l]);
        while (r < q[i].r) insert(a[++r]);
        while (l < q[i].l) remove(a[l++]);
        while (r > q[i].r) remove(a[r--]);
        q[i].ans1 = ans;
        q[i].ans2 = (i64)(r - l + 1) * (r - l) >> 1;
        if (q[i].ans1) {
            i64 x = gcd(q[i].ans1, q[i].ans2);
            q[i].ans1 /= x, q[i].ans2 /= x;
        } else q[i].ans2 = 1;
    }
    sort(q + 1, q + m + 1, comp2);
    for (int i = 1; i <= m; i++) cout << q[i].ans1 << '/' << q[i].ans2 << '\n';
    return 0;
}