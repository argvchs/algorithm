#include <cstring>
#include <iostream>
using namespace std;
const int N = 3e6 + 5;
int n, m, t, cnt[N], nex[N][128], tot;
string s;
void insert(int rt, string s) {
    for (char c : s) {
        if (!nex[rt][(int)c]) nex[rt][(int)c] = ++tot;
        rt = nex[rt][(int)c], ++cnt[rt];
    }
}
int query(int rt, string s) {
    for (char c : s) {
        if (!nex[rt][(int)c]) return 0;
        rt = nex[rt][(int)c];
    }
    return cnt[rt];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        memset(cnt, 0, tot * sizeof(int));
        memset(nex, 0, tot * sizeof(int[128]));
        cin >> n >> m, tot = 0;
        for (int i = 1; i <= n; i++) cin >> s, insert(0, s);
        for (int i = 1; i <= m; i++) cin >> s, cout << query(0, s) << '\n';
    }
    return 0;
}