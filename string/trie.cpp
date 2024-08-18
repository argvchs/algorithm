#include <cstring>
#include <iostream>
#include <string>
using namespace std;
const int N = 3e6 + 5;
int T, n, m, cnt;
string s;
struct node {
    int ch[128], cnt;
} t[N];
void insert(int rt, string s) {
    for (char c : s) {
        if (!t[rt].ch[(int)c]) t[rt].ch[(int)c] = ++cnt;
        rt = t[rt].ch[(int)c], ++t[rt].cnt;
    }
}
int query(int rt, string s) {
    for (char c : s) {
        if (!t[rt].ch[(int)c]) return 0;
        rt = t[rt].ch[(int)c];
    }
    return t[rt].cnt;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) {
        memset(t, 0, sizeof(node) * cnt);
        cin >> n >> m, cnt = 0;
        for (int i = 1; i <= n; i++) cin >> s, insert(0, s);
        for (int i = 1; i <= m; i++) cin >> s, cout << query(0, s) << '\n';
    }
}