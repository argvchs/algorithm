#include <cstring>
#include <iostream>
using namespace std;
constexpr int N = 3e6 + 5;
int n, m, t, cnt;
string s;
struct node {
    int val, ch[62];
} tt[N];
int id(char c) {
    if (isupper(c)) return c - 'A' + 10;
    if (islower(c)) return c - 'a' + 36;
    return c - '0';
}
void insert(string s) {
    int rt = 0;
    for (char c : s) {
        if (!tt[rt].ch[id(c)]) tt[rt].ch[id(c)] = ++cnt;
        rt = tt[rt].ch[id(c)], ++tt[rt].val;
    }
}
int query(string s) {
    int rt = 0;
    for (char c : s) {
        if (!tt[rt].ch[id(c)]) return 0;
        rt = tt[rt].ch[id(c)];
    }
    return tt[rt].val;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        memset(tt, 0, sizeof(node) * cnt);
        cnt = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> s, insert(s);
        for (int i = 1; i <= m; i++) cin >> s, cout << query(s) << '\n';
    }
    return 0;
}