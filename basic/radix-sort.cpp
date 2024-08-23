#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], b[N], c[0x10000];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memcpy(b, a, sizeof(b));
    for (int i = 1; i <= n; i++) ++c[b[i] & 0xffff];
    for (int i = 1; i < 0x10000; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) a[c[b[i] & 0xffff]--] = b[i];
    memset(c, 0, sizeof(c));
    memcpy(b, a, sizeof(b));
    for (int i = 1; i <= n; i++) ++c[b[i] >> 16 & 0xffff];
    for (int i = 1; i < 0x10000; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) a[c[b[i] >> 16 & 0xffff]--] = b[i];
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
}