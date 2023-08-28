#include <iostream>
#include <queue>
using namespace std;
const int N = 105;
int n, deg[N], head[N], cnt;
struct edge {
    int to, next;
} e[N << 1];
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
queue<int> Q;
void toposort() {
    for (int i = 1; i <= n; i++)
        if (!deg[i]) {
            cout << i << ' ';
            Q.push(i);
        }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = e[i].next) {
            int v = e[i].to;
            if (!--deg[v]) {
                cout << v << ' ';
                Q.push(v);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1, u; i <= n; i++)
        while (cin >> u && u) {
            ++deg[u];
            add(i, u);
        }
    toposort();
    return 0;
}