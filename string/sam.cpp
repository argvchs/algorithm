#include <algorithm>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
using namespace std;
using i64 = long long;
const int N = 2e6 + 5;
int a[N], c[N], cnt = 1, cur = 1;
i64 ans;
string s;
struct node {
    int fa, ch[26], cnt, len;
} t[N];
void insert(int c) {
    int p = exchange(cur, ++cnt);
    t[cur].len = t[p].len + 1, t[cur].cnt = 1;
    while (p && !t[p].ch[c]) t[p].ch[c] = cur, p = t[p].fa;
    if (!p) return void(t[cur].fa = 1);
    int q = t[p].ch[c];
    if (t[p].len + 1 == t[q].len) return void(t[cur].fa = q);
    t[++cnt].len = t[p].len + 1, t[cnt].fa = t[q].fa;
    memcpy(t[cnt].ch, t[q].ch, sizeof(t[cnt].ch));
    while (p && t[p].ch[c] == q) t[p].ch[c] = cnt, p = t[p].fa;
    t[q].fa = t[cur].fa = cnt;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    for (char c : s) insert(c - 'a');
    for (int i = 1; i <= cnt; i++) ++c[t[i].len];
    for (int i = 1; i <= cnt; i++) c[i] += c[i - 1];
    for (int i = 1; i <= cnt; i++) a[c[t[i].len]--] = i;
    for (int i = cnt; i >= 1; i--) {
        t[t[a[i]].fa].cnt += t[a[i]].cnt;
        if (t[a[i]].cnt > 1) ans = max(ans, (i64)t[a[i]].cnt * t[a[i]].len);
    }
    cout << ans;
}