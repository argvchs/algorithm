#include <iostream>
#include <string>
using namespace std;
const int N = 1e6 + 5;
int n, m, a[N], b[N], nxt[N];
string s, t;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s >> t;
    for (char c : s) a[++n] = c - 'A';
    for (char c : t) b[++m] = c - 'A';
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && b[i] != b[j + 1]) j = nxt[j];
        if (b[i] == b[j + 1]) ++j;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && a[i] != b[j + 1]) j = nxt[j];
        if (a[i] == b[j + 1]) ++j;
        if (j == m) cout << i - j + 1 << '\n', j = nxt[j];
    }
    for (int i = 1; i <= m; i++) cout << nxt[i] << ' ';
}