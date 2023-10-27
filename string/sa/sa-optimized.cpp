#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, m = 127, sa[N], rnk[N << 1], tmp[N << 1], cnt[N];
string s;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    for (char c : s) rnk[++n] = c;
    for (int i = 1; i <= n; i++) ++cnt[rnk[i]];
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[rnk[i]]--] = i;
    memcpy(tmp, rnk, sizeof(rnk));
    m = 0;
    for (int i = 1; i <= n; i++)
        if (tmp[sa[i]] == tmp[sa[i - 1]]) rnk[sa[i]] = m;
        else rnk[sa[i]] = ++m;
    for (int s = 1; s <= n; s <<= 1) {
        for (int i = 1; i <= s; i++) tmp[i] = i + n - s;
        for (int i = 1, j = s; i <= n; i++)
            if (sa[i] > s) tmp[++j] = sa[i] - s;
        memset(cnt, 0, sizeof(cnt));
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