#include <iostream>
#include <random>
#include <stack>
using namespace std;
const int N = 1e5 + 5;
int n, m, rt, cnt;
struct node {
    int l, r, val, siz;
    mt19937::result_type key;
    bool tag;
} tree[N];
mt19937 rng(random_device{}());
stack<int> S;
void maintain(int rt) {
    int l = tree[rt].l, r = tree[rt].r;
    tree[rt].siz = tree[l].siz + tree[r].siz + 1;
}
void spread(int rt) {
    if (!tree[rt].tag) return;
    int l = tree[rt].l, r = tree[rt].r;
    swap(tree[rt].l, tree[rt].r);
    tree[l].tag ^= true;
    tree[r].tag ^= true;
    tree[rt].tag = false;
}
auto split(int rt, int x) {
    if (!rt) return make_pair(0, 0);
    spread(rt);
    if (tree[tree[rt].l].siz >= x) {
        auto [l, r] = split(tree[rt].l, x);
        tree[rt].l = r;
        maintain(rt);
        return make_pair(l, rt);
    } else {
        auto [l, r] = split(tree[rt].r, x - tree[tree[rt].l].siz - 1);
        tree[rt].r = l;
        maintain(rt);
        return make_pair(rt, r);
    }
}
int merge(int lt, int rt) {
    if (!lt || !rt) return lt ^ rt;
    spread(lt);
    spread(rt);
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
int build() {
    int pre = 0;
    for (int i = 1; i <= n; i++) {
        tree[++cnt] = {0, 0, i, 1, rng()};
        while (!S.empty()) {
            if (tree[S.top()].key < tree[cnt].key) break;
            maintain(pre = S.top()), S.pop();
        }
        if (!S.empty()) tree[S.top()].r = cnt;
        tree[cnt].l = pre, pre = 0;
        S.push(cnt);
    }
    while (!S.empty()) maintain(pre = S.top()), S.pop();
    return pre;
}
void reverse(int x, int y) {
    auto [l, p] = split(rt, x - 1);
    auto [m, r] = split(p, y - x + 1);
    tree[m].tag ^= true;
    rt = merge(merge(l, m), r);
}
void output(int rt) {
    if (!rt) return;
    spread(rt);
    output(tree[rt].l);
    cout << tree[rt].val << ' ';
    output(tree[rt].r);
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