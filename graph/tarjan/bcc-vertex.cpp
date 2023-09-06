#include <iostream>
#include <stack>
#include <vector>
using namespace std;
const int N = 5e5 + 5, M = 2e6 + 5;
int n, m, dfn[N], low[N], head[N], idx, cnt;
struct edge {
    int to, next;
} e[M << 1];
stack<int> S;
vector<vector<int>> ans;
void add(int u, int v) { e[++cnt] = {v, head[u]}, head[u] = cnt; }
void addedge(int u, int v) { add(u, v), add(v, u); }
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx;
    S.push(u);
    for (int i = head[u]; i; i = e[i].next) {
        int v = e[i].to;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                int pre;
                ans.emplace_back().push_back(u);
                do {
                    pre = S.top(), S.pop();
                    ans.back().push_back(pre);
                } while (pre != v);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
    if (!fa && !head[u]) ans.emplace_back().push_back(u);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        if (u != v) addedge(u, v);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) tarjan(i, 0);
    cout << ans.size() << '\n';
    for (vector<int> &i : ans) {
        cout << i.size() << ' ';
        for (int j : i) cout << j << ' ';
        cout << '\n';
    }
    return 0;
}