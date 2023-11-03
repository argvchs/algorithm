#include <iostream>
using namespace std;
const int N = 3e5 + 5;
int n, m;
struct node {
    int fa, ch[2], val, sum;
    bool tag;
} t[N];
void maintain(int rt) { t[rt].sum = t[t[rt].ch[0]].sum ^ t[t[rt].ch[1]].sum ^ t[rt].val; }
void spread(int rt) {
    if (!t[rt].tag) return;
    swap(t[rt].ch[0], t[rt].ch[1]);
    t[t[rt].ch[0]].tag ^= 1, t[t[rt].ch[1]].tag ^= 1;
    t[rt].tag = false;
}
bool get(int rt) { return rt == t[t[rt].fa].ch[1]; }
void add(int lt, int rt, int x) { t[lt].fa = rt, t[rt].ch[x] = lt; }
bool isroot(int rt) { return rt != t[t[rt].fa].ch[0] && rt != t[t[rt].fa].ch[1]; }
void rotate(int rt) {
    int fa = t[rt].fa, x = get(rt);
    if (!isroot(fa)) add(rt, t[fa].fa, get(fa));
    add(t[rt].ch[!x], fa, x), t[rt].fa = t[fa].fa, add(fa, rt, !x);
    maintain(fa), maintain(rt);
}
void spreadall(int rt) {
    if (!isroot(rt)) spreadall(t[rt].fa);
    spread(rt);
}
void splay(int rt) {
    spreadall(rt);
    for (int fa; fa = t[rt].fa, !isroot(rt); rotate(rt))
        if (!isroot(fa)) rotate(get(rt) == get(fa) ? fa : rt);
}
void access(int rt) {
    for (int las = 0; rt; las = rt, rt = t[rt].fa)
        splay(rt), t[rt].ch[1] = las, maintain(rt);
}
void makeroot(int rt) { access(rt), splay(rt), t[rt].tag ^= 1; }
int findroot(int rt) {
    access(rt), splay(rt);
    while (t[rt].ch[0]) rt = t[rt].ch[0];
    return splay(rt), rt;
}
void link(int lt, int rt) {
    makeroot(lt);
    if (findroot(rt) != lt) t[lt].fa = rt;
}
void cut(int lt, int rt) {
    makeroot(lt);
    if (findroot(rt) == lt && t[rt].fa == lt && !t[rt].ch[0])
        t[rt].fa = t[lt].ch[1] = 0, maintain(lt);
}
int query(int lt, int rt) {
    makeroot(lt), access(rt), splay(rt);
    return t[rt].sum;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> t[i].val;
    for (int i = 1, op, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (!op) cout << query(x, y) << '\n';
        else if (op == 1) link(x, y);
        else if (op == 2) cut(x, y);
        else splay(x), t[x].val = y;
    }
    return 0;
}