#include <iostream>
#include <stack>
using namespace std;
const int N = 1e6 + 5;
int n, m, dfn[N << 1], low[N << 1], belong[N << 1], head[N << 1], idx, cnt, tot, ans;
bool vis[N << 1];
stack<int> S;
struct edge {
    int to, next;
} e[N << 1];
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void tarjan(int u) {
    dfn[u] = low[u] = ++idx, vis[u] = true;
    S.push(u);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++tot;
        while (S.top() != u) {
            int v = S.top();
            belong[v] = tot, vis[v] = false;
            S.pop();
        }
        belong[u] = tot, vis[u] = false;
        S.pop();
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v, a, b; i <= m; i++) {
        cin >> u >> a >> v >> b;
        add(u + a * n, v + (b ^ 1) * n);
        add(v + b * n, u + (a ^ 1) * n);
    }
    for (int i = 1; i <= (n << 1); i++)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= n; i++)
        if (belong[i] == belong[i + n]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    cout << "POSSIBLE\n";
    for (int i = 1; i <= n; i++) cout << (belong[i] < belong[i + n]) << ' ';
    return 0;
}