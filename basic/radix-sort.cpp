#include <cstring>
#include <iostream>
using namespace std;
const int N = 1e5 + 5;
int n, a[N], tmp[N], cnt[256];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    memcpy(tmp, a, sizeof(tmp));
    for (int i = 1; i <= n; i++) ++cnt[tmp[i] & 255];
    for (int i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) a[cnt[tmp[i] & 255]--] = tmp[i];
    memset(cnt, 0, sizeof(cnt));
    memcpy(tmp, a, sizeof(tmp));
    for (int i = 1; i <= n; i++) ++cnt[tmp[i] >> 8 & 255];
    for (int i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) a[cnt[tmp[i] >> 8 & 255]--] = tmp[i];
    memset(cnt, 0, sizeof(cnt));
    memcpy(tmp, a, sizeof(tmp));
    for (int i = 1; i <= n; i++) ++cnt[tmp[i] >> 16 & 255];
    for (int i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) a[cnt[tmp[i] >> 16 & 255]--] = tmp[i];
    memset(cnt, 0, sizeof(cnt));
    memcpy(tmp, a, sizeof(tmp));
    for (int i = 1; i <= n; i++) ++cnt[tmp[i] >> 24 & 255];
    for (int i = 1; i <= 255; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) a[cnt[tmp[i] >> 24 & 255]--] = tmp[i];
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    return 0;
}