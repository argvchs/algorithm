#include <cstring>
#include <iostream>
using namespace std;
const int N = 3e6 + 5;
int n, m, t, cnt;
char s[N];
struct node {
    int val, son[62];
} tree[N];
int id(char c) {
    if (isdigit(c)) return c - '0';
    if (isupper(c)) return c - 'A' + 10;
    return c - 'a' + 36;
}
void insert(char (&s)[N]) {
    int rt = 0, len = strlen(s + 1);
    for (int i = 1; i <= len; i++) {
        int x = id(s[i]);
        if (!tree[rt].son[x]) tree[rt].son[x] = ++cnt;
        rt = tree[rt].son[x], ++tree[rt].val;
    }
}
int query(char (&s)[N]) {
    int rt = 0, len = strlen(s + 1);
    for (int i = 1; i <= len; i++) {
        int x = id(s[i]);
        if (!tree[rt].son[x]) return 0;
        rt = tree[rt].son[x];
    }
    return tree[rt].val;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        memset(&tree, 0, sizeof(node) * (cnt + 1));
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