#include <iostream>
#include <utility>
using namespace std;
const int N = 3e5 + 5;
int n, m;
struct node {
    int fa, ch[2], val, sum;
    bool rev;
} t[N];
void pushup(int rt) { t[rt].sum = t[t[rt].ch[0]].sum ^ t[t[rt].ch[1]].sum ^ t[rt].val; }
void push(int rt) { swap(t[rt].ch[0], t[rt].ch[1]), t[rt].rev ^= true; }
void pushdown(int rt) {
    if (t[rt].rev) push(t[rt].ch[0]), push(t[rt].ch[1]), t[rt].rev = false;
}
bool get(int rt) { return rt == t[t[rt].fa].ch[1]; }
bool isroot(int rt) { return rt != t[t[rt].fa].ch[0] && rt != t[t[rt].fa].ch[1]; }
void rotate(int rt) {
    int fa = t[rt].fa, x = get(rt);
    if (!isroot(fa)) t[t[fa].fa].ch[get(fa)] = rt;
    t[rt].fa = t[fa].fa, t[fa].fa = rt, t[t[rt].ch[!x]].fa = fa;
    t[fa].ch[x] = t[rt].ch[!x], t[rt].ch[!x] = fa;
    pushup(fa), pushup(rt);
}
void pushall(int rt) {
    if (!isroot(rt)) pushall(t[rt].fa);
    pushdown(rt);
}
void splay(int rt) {
    pushall(rt);
    for (int fa; fa = t[rt].fa, !isroot(rt); rotate(rt))
        if (!isroot(fa)) rotate(get(rt) == get(fa) ? fa : rt);
}
void access(int rt) {
    for (int ch = 0; rt; ch = rt, rt = t[rt].fa) splay(rt), t[rt].ch[1] = ch, pushup(rt);
}
void makeroot(int rt) { access(rt), splay(rt), push(rt); }
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
        t[rt].fa = t[lt].ch[1] = 0, pushup(lt);
}
void split(int lt, int rt) { makeroot(lt), access(rt), splay(rt); }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> t[i].val;
    for (int i = 1, op, x, y; i <= m; i++) {
        cin >> op >> x >> y;
        if (!op) split(x, y), cout << t[y].sum << '\n';
        else if (op == 1) link(x, y);
        else if (op == 2) cut(x, y);
        else splay(x), t[x].val = y;
    }
}