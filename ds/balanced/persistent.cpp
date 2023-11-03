#include <iostream>
#include <random>
#include <tuple>
using namespace std;
using m64 = pair<int, int>;
using m96 = tuple<int, int, int>;
const int N = 5e5 + 5;
int n, rt[N], cnt;
struct node {
    int l, r, val, cnt, siz;
    mt19937::result_type key;
} t[N * 75];
mt19937 gen(random_device{}());
void maintain(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + t[rt].cnt; }
m64 split(int rt, int x) {
    if (!rt) return {};
    t[++cnt] = t[rt], rt = cnt;
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
    t[++cnt] = t[rt], rt = cnt;
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
        t[++cnt] = t[lt], lt = cnt, t[lt].r = merge(t[lt].r, rt);
        return maintain(lt), lt;
    } else {
        t[++cnt] = t[rt], rt = cnt, t[rt].l = merge(lt, t[rt].l);
        return maintain(rt), rt;
    }
}
int insert(int rt, int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    t[++cnt] = t[m];
    if (m) m = cnt, ++t[m].cnt, ++t[m].siz;
    else t[m = cnt] = {0, 0, x, 1, 1, gen()};
    return merge(merge(l, m), r);
}
int remove(int rt, int x) {
    auto [l, p] = split(rt, x);
    auto [m, r] = split(p, x + 1);
    t[++cnt] = t[m], m = cnt;
    if (t[m].cnt > 1) --t[m].cnt, --t[m].siz;
    else m = 0, --cnt;
    return merge(merge(l, m), r);
}
int queryrnk(int rt, int x) { return t[get<0>(split(rt, x))].siz + 1; }
int querykth(int rt, int x) { return t[get<1>(splitrnk(rt, x))].val; }
int querypre(int rt, int x) { return querykth(rt, queryrnk(rt, x) - 1); }
int querynex(int rt, int x) { return querykth(rt, queryrnk(rt, x + 1)); }
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