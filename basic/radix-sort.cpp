#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], b[N], c[256];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memcpy(b, a, sizeof(b));
    for (int i = 1; i <= n; i++) ++c[b[i] & 255];
    for (int i = 1; i <= 255; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) a[c[b[i] & 255]--] = b[i];
    memset(c, 0, sizeof(c));
    memcpy(b, a, sizeof(b));
    for (int i = 1; i <= n; i++) ++c[b[i] >> 8 & 255];
    for (int i = 1; i <= 255; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) a[c[b[i] >> 8 & 255]--] = b[i];
    memset(c, 0, sizeof(c));
    memcpy(b, a, sizeof(b));
    for (int i = 1; i <= n; i++) ++c[b[i] >> 16 & 255];
    for (int i = 1; i <= 255; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) a[c[b[i] >> 16 & 255]--] = b[i];
    memset(c, 0, sizeof(c));
    memcpy(b, a, sizeof(b));
    for (int i = 1; i <= n; i++) ++c[b[i] >> 24 & 255];
    for (int i = 1; i <= 255; i++) c[i] += c[i - 1];
    for (int i = n; i >= 1; i--) a[c[b[i] >> 24 & 255]--] = b[i];
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    return 0;
}