#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N = 5e5 + 5, M = 2e6 + 5;
int n, m, dfn[N], low[N], head[N], idx, cnt = 1;
struct edge {
    int to, nxt;
} e[M << 1];
stack<int> S;
vector<vector<int>> ans;
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx, S.push(u);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v, i ^ 1);
            low[u] = min(low[u], low[v]);
        } else if (i != fa) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] != low[u]) return;
    int top;
    ans.emplace_back();
    do ans.back().push_back(top = S.top()), S.pop();
    while (top != u);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, addedge(u, v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
    cout << ans.size() << '\n';
    for (const auto &i : ans) {
        cout << i.size() << ' ';
        for (int j : i) cout << j << ' ';
        cout << '\n';
    }
}