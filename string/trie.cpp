#include <cstring>
#include <iostream>
using namespace std;
const int N = 3e6 + 5;
int n, m, tt, cnt;
char s[N];
struct node {
    int val, ch[62];
} t[N];
int id(char c) {
    if (isupper(c)) return c - 'A' + 10;
    if (islower(c)) return c - 'a' + 36;
    return c - '0';
}
void insert(char *s) {
    int rt = 0, len = strlen(s + 1);
    for (int i = 1; i <= len; i++) {
        int x = id(s[i]);
        if (!t[rt].ch[x]) t[rt].ch[x] = ++cnt;
        rt = t[rt].ch[x], ++t[rt].val;
    }
}
int query(char *s) {
    int rt = 0, len = strlen(s + 1);
    for (int i = 1; i <= len; i++) {
        int x = id(s[i]);
        if (!t[rt].ch[x]) return 0;
        rt = t[rt].ch[x];
    }
    return t[rt].val;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> tt;
    while (tt--) {
        memset(t, 0, sizeof(node) * cnt);
        cnt = 0;
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            cin.ignore().get(s + 1, N);
            insert(s);
        }
        for (int i = 1; i <= m; i++) {
            cin.ignore().get(s + 1, N);
            cout << query(s) << '\n';
        }
    }
    return 0;
}