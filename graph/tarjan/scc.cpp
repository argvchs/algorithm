#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N = 1e4 + 5, M = 1e5 + 5;
int n, m, dfn[N], low[N], head[N], idx, cnt;
bool vis[N];
struct edge {
    int to, nxt;
} e[M];
stack<int> S;
vector<vector<int>> ans;
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void tarjan(int u) {
    dfn[u] = low[u] = ++idx, vis[u] = true, S.push(u);
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (vis[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] != low[u]) return;
    int top;
    ans.emplace_back();
    do ans.back().push_back(top = S.top()), vis[top] = false, S.pop();
    while (top != u);
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) cin >> u >> v, add(u, v);
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i);
    for (auto &i : ans) sort(i.begin(), i.end());
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (const auto &i : ans) {
        for (int j : i) cout << j << ' ';
        cout << '\n';
    }
}