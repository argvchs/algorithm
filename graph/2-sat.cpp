#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N = 2e6 + 5;
int n, m, dfn[N], low[N], belong[N], idx, tot, ans;
bool vis[N];
vector<int> G[N];
stack<int> S;
void tarjan(int u) {
    dfn[u] = low[u] = ++idx, vis[u] = true;
    S.push(u);
    for (int v : G[u])
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (vis[v]) low[u] = min(low[u], dfn[v]);
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
        G[u + a * n].push_back(v + (b ^ 1) * n);
        G[v + b * n].push_back(u + (a ^ 1) * n);
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