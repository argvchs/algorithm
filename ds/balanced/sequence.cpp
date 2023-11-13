#include <chrono>
#include <iostream>
#include <random>
#include <stack>
using namespace std;
using p32 = pair<int, int>;
const int N = 1e5 + 5;
int n, m, rt, cnt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
    bool tag;
} t[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
stack<int> S;
void maintain(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
void spread(int rt) {
    if (!t[rt].tag) return;
    swap(t[rt].l, t[rt].r);
    t[t[rt].l].tag ^= 1, t[t[rt].r].tag ^= 1;
    t[rt].tag = false;
}
p32 split(int rt, int x) {
    if (!rt) return {};
    spread(rt);
    if (t[t[rt].l].siz >= x) {
        auto [l, r] = split(t[rt].l, x);
        t[rt].l = r, maintain(rt);
        return {l, rt};
    } else {
        auto [l, r] = split(t[rt].r, x - t[t[rt].l].siz - 1);
        t[rt].r = l, maintain(rt);
        return {rt, r};
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    spread(lt), spread(rt);
    if (t[lt].key < t[rt].key) {
        t[lt].r = merge(t[lt].r, rt);
        return maintain(lt), lt;
    } else {
        t[rt].l = merge(lt, t[rt].l);
        return maintain(rt), rt;
    }
}
int build() {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        t[++cnt] = {0, 0, i, 1, rng()};
        while (!S.empty()) {
            if (t[S.top()].key < t[cnt].key) break;
            maintain(t[cnt].l = S.top()), S.pop();
        }
        if (!S.empty()) t[S.top()].r = cnt;
        S.push(cnt);
    }
    while (!S.empty()) maintain(ret = S.top()), S.pop();
    return ret;
}
void reverse(int x, int y) {
    auto [l, _] = split(rt, x - 1);
    auto [m, r] = split(_, y - x + 1);
    t[m].tag ^= 1;
    rt = merge(merge(l, m), r);
}
void output(int rt) {
    if (!rt) return;
    spread(rt);
    output(t[rt].l), cout << t[rt].val << ' ', output(t[rt].r);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    rt = build();
    for (int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        reverse(l, r);
    }
    output(rt);
    return 0;
}