#include <iostream>
#include <tuple>
using namespace std;
int n, p;
tuple<int, int, int> exgcd(int a, int b) {
    if (!b) return {1, 0, a};
    auto [x, y, gcd] = exgcd(b, a % b);
    return {y, x - a / b * y, gcd};
}
int inverse(int a, int p) { return (get<0>(exgcd(a, p)) + p) % p; }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cout << inverse(i, p) << '\n';
    return 0;
}