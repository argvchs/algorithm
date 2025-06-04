#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int N = 3e6 + 5;
int T, n, q, cnt;
string s;
struct node {
    int ch[62], cnt;
} t[N];
int id(char c) {
    if (isupper(c)) return c - 'A';
    if (islower(c)) return c - 'a' + 26;
    return c - '0' + 52;
}
void insert(int rt, const string &s) {
    for (char c : s) {
        if (!t[rt].ch[id(c)]) t[rt].ch[id(c)] = ++cnt;
        rt = t[rt].ch[id(c)], ++t[rt].cnt;
    }
}
int query(int rt, const string &s) {
    for (char c : s) {
        if (!t[rt].ch[id(c)]) return 0;
        rt = t[rt].ch[id(c)];
    }
    return t[rt].cnt;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        memset(t, 0, sizeof(node) * (cnt + 1));
        cin >> n >> q, cnt = 0;
        for (int i = 1; i <= n; i++) cin >> s, insert(0, s);
        for (int i = 1; i <= q; i++) cin >> s, cout << query(0, s) << '\n';
    }
}