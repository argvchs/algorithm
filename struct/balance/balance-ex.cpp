#include <climits>
#include <iostream>
#include <random>
#include <tuple>
using namespace std;
const int N = 2e6 + 5;
int n, m, rt, cnt, pre, ans;
mt19937 rng(random_device{}());
struct node {
    int l, r, val, cnt, siz;
    mt19937::result_type key;
} tree[N];
void maintain(int rt) {
    int l = tree[rt].l, r = tree[rt].r;
    tree[rt].siz = tree[l].siz + tree[r].siz + tree[rt].cnt;
}
pair<int, int> split(int rt, int x) {
    if (!rt) return {};
    if (tree[rt].val >= x) {
        auto [l, r] = split(tree[rt].l, x);
        tree[rt].l = r;
        maintain(rt);
        return {l, rt};
    } else {
        auto [l, r] = split(tree[rt].r, x);
        tree[rt].r = l;
        maintain(rt);
        return {rt, r};
    }
}
tuple<int, int, int> splitrank(int rt, int x) {
    if (!rt) return {};
    if (tree[tree[rt].l].siz >= x) {
        auto [l, m, r] = splitrank(tree[rt].l, x);
        tree[rt].l = r;
        maintain(rt);
        return {l, m, rt};
    } else if (tree[tree[rt].l].siz + tree[rt].cnt >= x) {
        int l = tree[rt].l, r = tree[rt].r;
        tree[rt].l = tree[rt].r = 0;
        maintain(rt);
        return {l, rt, r};
    } else {
        auto [l, m, r] = splitrank(tree[rt].r, x - tree[tree[rt].l].siz - tree[rt].cnt);
        tree[rt].r = l;
        maintain(rt);
        return {rt, m, r};
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt ^ rt;
    if (tree[lt].key < tree[rt].key) {
        tree[lt].r = merge(tree[lt].r, rt);
        maintain(lt);
        return lt;
    } else {
        tree[rt].l = merge(lt, tree[rt].l);
        maintain(rt);
        return rt;
    }
}
void insert(int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    if (m) ++tree[m].cnt, ++tree[m].siz;
    else tree[m = ++cnt] = {0, 0, x, 1, 1, rng()};
    rt = merge(merge(l, m), r);
}
void remove(int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    if (tree[m].cnt > 1) --tree[m].cnt, --tree[m].siz;
    else m = 0;
    rt = merge(merge(l, m), r);
}
int queryrank(int x) {
    auto [l, r] = split(rt, x);
    int res = tree[l].siz + 1;
    rt = merge(l, r);
    return res;
}
int querykth(int x) {
    if (x < 1) return INT_MIN;
    if (x > tree[rt].siz) return INT_MAX;
    auto [l, m, r] = splitrank(rt, x);
    int res = tree[m].val;
    rt = merge(merge(l, m), r);
    return res;
}
int querypre(int x) { return querykth(queryrank(x) - 1); }
int querysuc(int x) { return querykth(queryrank(x + 1)); }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) {
        cin >> x;
        insert(x);
    }
    for (int i = 1, op, x; i <= m; i++) {
        cin >> op >> x;
        x ^= pre;
        if (op == 1) insert(x);
        else if (op == 2) remove(x);
        else if (op == 3) ans ^= pre = queryrank(x);
        else if (op == 4) ans ^= pre = querykth(x);
        else if (op == 5) ans ^= pre = querypre(x);
        else ans ^= pre = querysuc(x);
    }
    cout << ans;
    return 0;
}