#include <iostream>
#include <queue>
using namespace std;
const int N = 105, M = 1e4 + 5;
int n, deg[N], head[N], cnt;
struct edge {
    int to, nxt;
} e[M];
queue<int> Q;
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void toposort() {
    for (int i = 1; i <= n; i++)
        if (!deg[i]) cout << i << ' ', Q.push(i);
    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].to;
            if (!--deg[v]) cout << v << ' ', Q.push(v);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, x; i <= n; i++)
        while (cin >> x && x) ++deg[x], add(i, x);
    toposort();
    return 0;
}