#include <iostream>
#include <limits>
#include <random>
#include <tuple>
using namespace std;
using m64 = pair<int, int>;
using m96 = tuple<int, int, int>;
constexpr int N = 5e5 + 5;
int n, rt[N], cnt;
struct node {
    int l, r, val, cnt, siz;
    mt19937::result_type key;
} t[N * 75];
mt19937 gen(random_device{}());
void maintain(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + t[rt].cnt; }
m64 split(int rt, int x) {
    if (!rt) return {};
    int cur = ++cnt;
    if (t[rt].val >= x) {
        auto [l, r] = split(t[rt].l, x);
        t[cur] = t[rt], t[cur].l = r, maintain(cur);
        return {l, cur};
    } else {
        auto [l, r] = split(t[rt].r, x);
        t[cur] = t[rt], t[cur].r = l, maintain(cur);
        return {cur, r};
    }
}
m96 splitrnk(int rt, int x) {
    if (!rt) return {};
    int cur = ++cnt;
    if (t[t[rt].l].siz >= x) {
        auto [l, m, r] = splitrnk(t[rt].l, x);
        t[cur] = t[rt], t[cur].l = r, maintain(cur);
        return {l, m, cur};
    } else if (t[t[rt].l].siz + t[rt].cnt >= x) {
        int l = t[rt].l, r = t[rt].r;
        t[cur] = t[rt], t[cur].l = t[cur].r = 0, maintain(cur);
        return {l, cur, r};
    } else {
        auto [l, m, r] = splitrnk(t[rt].r, x - t[t[rt].l].siz - t[rt].cnt);
        t[cur] = t[rt], t[cur].r = l, maintain(cur);
        return {cur, m, r};
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    int cur = ++cnt;
    if (t[lt].key < t[rt].key) {
        t[cur] = t[lt], t[cur].r = merge(t[lt].r, rt), maintain(cur);
        return cur;
    } else {
        t[cur] = t[rt], t[cur].l = merge(lt, t[rt].l), maintain(cur);
        return cur;
    }
}
int insert(int rt, int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    int cur = ++cnt;
    if (m) t[cur] = t[m], ++t[cur].cnt, ++t[cur].siz;
    else t[cur] = {0, 0, x, 1, 1, gen()};
    return merge(merge(l, cur), r);
}
int remove(int rt, int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    int cur = ++cnt;
    if (t[m].cnt > 1) t[cur] = t[m], --t[cur].cnt, --t[cur].siz;
    else cur = 0, --cnt;
    return merge(merge(l, cur), r);
}
int queryrnk(int &rt, int x) {
    auto [l, r] = split(rt, x);
    int ret = t[l].siz + 1;
    rt = merge(l, r);
    return ret;
}
int querykth(int &rt, int x) {
    if (x < 1) return numeric_limits<int>::min();
    if (x > t[rt].siz) return numeric_limits<int>::max();
    auto [l, m, r] = splitrnk(rt, x);
    int ret = t[m].val;
    rt = merge(merge(l, m), r);
    return ret;
}
int querypre(int &rt, int x) { return querykth(rt, queryrnk(rt, x) - 1); }
int querynex(int &rt, int x) { return querykth(rt, queryrnk(rt, x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, ver, op, x; i <= n; i++) {
        cin >> ver >> op >> x;
        if (op == 1) rt[i] = insert(rt[ver], x);
        else if (op == 2) rt[i] = remove(rt[ver], x);
        else if (op == 3) cout << queryrnk(rt[i] = rt[ver], x) << '\n';
        else if (op == 4) cout << querykth(rt[i] = rt[ver], x) << '\n';
        else if (op == 5) cout << querypre(rt[i] = rt[ver], x) << '\n';
        else cout << querynex(rt[i] = rt[ver], x) << '\n';
    }
    return 0;
}