#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e6 + 5;
int n, v = 127, a[N], b[N], c[N], sa[N];
string s;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    for (char c : s) a[++n] = c;
    for (int i = 1; i <= n; i++) ++c[a[i]];
    for (int i = 1; i <= v; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) sa[c[a[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        for (int i = 1; i <= k; i++) b[i] = i + n - k;
        for (int i = 1, j = k; i <= n; i++)
            if (sa[i] > k) b[++j] = sa[i] - k;
        memset(c, 0, sizeof(c));
        for (int i = 1; i <= n; i++) ++c[a[b[i]]];
        for (int i = 1; i <= v; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[a[b[i]]]--] = b[i];
        memcpy(b, a, sizeof(a)), v = 0;
        for (int i = 1; i <= n; i++)
            if (b[sa[i]] == b[sa[i - 1]] && b[sa[i] + k] == b[sa[i - 1] + k])
                a[sa[i]] = v;
            else a[sa[i]] = ++v;
        if (v == n) break;
    }
    for (int i = 1; i <= n; i++) cout << sa[i] << ' ';
    return 0;
}