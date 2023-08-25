#include <climits>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 2e6 + 5;
int n, m = CHAR_MAX, sa[N], rnk[N], tmp[N], cnt[N];
string s;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    n = s.size(), s = " "s + s;
    for (int i = 1; i <= n; i++) ++cnt[rnk[i] = s[i]];
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rnk[i]]--] = i;
    memcpy(tmp, rnk, sizeof(rnk));
    m = 0;
    for (int i = 1; i <= n; i++)
        if (tmp[sa[i]] == tmp[sa[i - 1]]) rnk[sa[i]] = m;
        else rnk[sa[i]] = ++m;
    for (int s = 1; s <= n; s <<= 1) {
        memset(cnt, 0, sizeof(cnt));
        memcpy(tmp, sa, sizeof(sa));
        for (int i = 1; i <= n; i++) ++cnt[rnk[tmp[i] + s]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rnk[tmp[i] + s]]--] = tmp[i];
        memset(cnt, 0, sizeof(cnt));
        memcpy(tmp, sa, sizeof(sa));
        for (int i = 1; i <= n; i++) ++cnt[rnk[tmp[i]]];
        for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (int i = n; i >= 1; i--) sa[cnt[rnk[tmp[i]]]--] = tmp[i];
        memcpy(tmp, rnk, sizeof(rnk));
        m = 0;
        for (int i = 1; i <= n; i++)
            if (tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + s] == tmp[sa[i - 1] + s])
                rnk[sa[i]] = m;
            else rnk[sa[i]] = ++m;
        if (m == n) break;
    }
    for (int i = 1; i <= n; i++) cout << sa[i] << ' ';
    return 0;
}