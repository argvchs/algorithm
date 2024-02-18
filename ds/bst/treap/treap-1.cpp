#include <chrono>
#include <iostream>
#include <random>
using namespace std;
const int N = 1e5 + 5;
int n, rt, cnt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
} t[N];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int newnode(int x) { return t[++cnt] = {0, 0, x, 1, rng()}, cnt; }
void pushup(int rt) { t[rt].siz = t[t[rt].l].siz + t[t[rt].r].siz + 1; }
void split(int rt, int x, int &l, int &r) {
    if (!rt) return void(l = r = 0);
    if (t[rt].val >= x) split(t[r = rt].l, x, l, t[rt].l);
    else split(t[l = rt].r, x, t[rt].r, r);
    pushup(rt);
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt + rt;
    if (t[lt].key < t[rt].key) t[lt].r = merge(t[lt].r, rt);
    else t[rt].l = merge(lt, t[rt].l), lt = rt;
    return pushup(lt), lt;
}
void insert(int &rt, int x) {
    int l, r;
    split(rt, x, l, r);
    rt = merge(merge(l, newnode(x)), r);
}
void remove(int &rt, int x) {
    int l, m, r;
    split(rt, x, l, m), split(m, x + 1, m, r);
    rt = merge(merge(l, merge(t[m].l, t[m].r)), r);
}
int queryrnk(int rt, int x) {
    if (!rt) return 1;
    if (t[rt].val >= x) return queryrnk(t[rt].l, x);
    return queryrnk(t[rt].r, x) + t[t[rt].l].siz + 1;
}
int querykth(int rt, int x) {
    if (t[t[rt].l].siz + 1 == x) return t[rt].val;
    if (t[t[rt].l].siz >= x) return querykth(t[rt].l, x);
    return querykth(t[rt].r, x - t[t[rt].l].siz - 1);
}
int querypre(int rt, int x) { return querykth(rt, queryrnk(rt, x) - 1); }
int querynxt(int rt, int x) { return querykth(rt, queryrnk(rt, x + 1)); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, op, x; i <= n; i++) {
        cin >> op >> x;
        if (op == 1) insert(rt, x);
        else if (op == 2) remove(rt, x);
        else if (op == 3) cout << queryrnk(rt, x) << '\n';
        else if (op == 4) cout << querykth(rt, x) << '\n';
        else if (op == 5) cout << querypre(rt, x) << '\n';
        else cout << querynxt(rt, x) << '\n';
    }
}