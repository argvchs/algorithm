#include <cctype>
#include <iostream>
using namespace std;
using i64 = long long;
int a, b, p, q;
int qpow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = (i64)a * a % p)
        if (b & 1) ret = (i64)ret * a % p;
    return ret;
}
int phi(int n) {
    int ret = 1;
    for (int i = 2; i * i <= n; i++)
        while (n % i == 0) n /= i, ret *= i - !!(n % i);
    if (n != 1) ret *= n - 1;
    return ret;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> a >> p, q = phi(p);
    char c = cin.get();
    while (isspace(c)) c = cin.get();
    while (isdigit(c)) {
        b = b * 10 + c - '0', c = cin.get();
        if (b >= q) b = b % q + q;
    }
    cout << qpow(a, b, p);
}