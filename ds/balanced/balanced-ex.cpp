#include <iostream>
#include <random>
#include <tuple>
using namespace std;
using m64 = pair<int, int>;
using m96 = tuple<int, int, int>;
const int N = 2e6 + 5;
int n, m, rt, cnt, las, ans;
struct node {
    int l, r, val, cnt, siz;
    mt19937::result_type key;
} t[N];
mt19937 gen(random_device{}());
void maintain(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + t[rt].cnt; }
m64 split(int rt, int x) {
    if (!rt) return {};
    if (t[rt].val >= x) {
        auto [l, r] = split(t[rt].l, x);
        t[rt].l = r, maintain(rt);
        return {l, rt};
    } else {
        auto [l, r] = split(t[rt].r, x);
        t[rt].r = l, maintain(rt);
        return {rt, r};
    }
}
m96 splitrnk(int rt, int x) {
    if (!rt) return {};
    if (t[t[rt].l].siz >= x) {
        auto [l, m, r] = splitrnk(t[rt].l, x);
        t[rt].l = r, maintain(rt);
        return {l, m, rt};
    } else if (t[t[rt].l].siz + t[rt].cnt >= x) {
        int l = t[rt].l, r = t[rt].r;
        t[rt].l = t[rt].r = 0, maintain(rt);
        return {l, rt, r};
    } else {
        auto [l, m, r] = splitrnk(t[rt].r, x - t[t[rt].l].siz - t[rt].cnt);
        t[rt].r = l, maintain(rt);
        return {rt, m, r};
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (t[lt].key < t[rt].key) {
        t[lt].r = merge(t[lt].r, rt), maintain(lt);
        return lt;
    } else {
        t[rt].l = merge(lt, t[rt].l), maintain(rt);
        return rt;
    }
}
void insert(int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    if (m) ++t[m].cnt, ++t[m].siz;
    else t[m = ++cnt] = {0, 0, x, 1, 1, gen()};
    rt = merge(merge(l, m), r);
}
void remove(int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    if (t[m].cnt > 1) --t[m].cnt, --t[m].siz;
    else m = 0;
    rt = merge(merge(l, m), r);
}
int queryrnk(int x) {
    auto [l, r] = split(rt, x);
    int ret = t[l].siz + 1;
    rt = merge(l, r);
    return ret;
}
int querykth(int x) {
    if (x < 1) return numeric_limits<int>::min();
    if (x > t[rt].siz) return numeric_limits<int>::max();
    auto [l, m, r] = splitrnk(rt, x);
    int ret = t[m].val;
    rt = merge(merge(l, m), r);
    return ret;
}
int querypre(int x) { return querykth(queryrnk(x) - 1); }
int querynex(int x) { return querykth(queryrnk(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        insert(x);
    }
    for (int i = 1, op, x; i <= m; i++) {
        cin >> op >> x, x ^= las;
        if (op == 1) insert(x);
        else if (op == 2) remove(x);
        else if (op == 3) ans ^= las = queryrnk(x);
        else if (op == 4) ans ^= las = querykth(x);
        else if (op == 5) ans ^= las = querypre(x);
        else ans ^= las = querynex(x);
    }
    cout << ans;
    return 0;
}