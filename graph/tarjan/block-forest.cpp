#include <iostream>
#include <stack>
using namespace std;
const int N = 1e4 + 5, M = 2e4 + 5;
int n, m, k, dfn[N], low[N], f[N << 1][25], val[N], sum[N << 1], dis1[N], dis2[N << 1],
    dep[N << 1], head1[N], head2[N << 1], idx, cnt, tot, ans1, ans2;
struct edge {
    int to, next, w;
} e[M << 2];
stack<int> S;
void add1(int u, int v, int w) { e[++cnt] = {v, head1[u], w}, head1[u] = cnt; }
void add2(int u, int v, int w) { e[++cnt] = {v, head2[u], w}, head2[u] = cnt; }
void addedge1(int u, int v, int w) { add1(u, v, w), add1(v, u, w); }
void addedge2(int u, int v, int w) { add2(u, v, w), add2(v, u, w); }
void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx, S.push(u);
    for (int i = head1[u]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w;
        if (!dfn[v]) {
            dis1[v] = dis1[u] + w, val[v] = w;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] < dfn[u]) continue;
            int pre, k;
            sum[++tot] = dis1[S.top()] - dis1[u] + val[S.top()];
            addedge2(u, tot, 0);
            do {
                k = dis1[pre = S.top()] - dis1[u], S.pop();
                addedge2(pre, tot, min(k, sum[tot] - k));
            } while (pre != v);
        } else if (dfn[v] < dfn[fa]) low[u] = min(low[u], dfn[v]), val[u] = w;
    }
}
void dfs(int u, int fa) {
    f[u][0] = fa, dep[u] = dep[fa] + 1;
    for (int i = 1; i <= 20; i++) f[u][i] = f[f[u][i - 1]][i - 1];
    for (int i = head2[u]; i; i = e[i].next) {
        int v = e[i].to, w = e[i].w;
        if (v != fa) dis2[v] = dis2[u] + w, dfs(v, u);
    }
}
int solve(int u, int v) {
    int ret = dis2[u] + dis2[v];
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 20; i >= 0; i--)
        if (dep[f[u][i]] >= dep[v]) u = f[u][i];
    if (u == v) return ret - (dis2[u] << 1);
    for (int i = 20; i >= 0; i--)
        if (f[u][i] != f[v][i]) u = f[u][i], v = f[v][i];
    if (f[u][0] <= n) return ret - (dis2[f[u][0]] << 1);
    int k = abs(dis1[u] - dis1[v]);
    return ret - dis2[u] - dis2[v] + min(k, sum[f[u][0]] - k);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> k, tot = n;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        addedge1(u, v, w);
    }
    tarjan(1, 0);
    dfs(1, 0);
    for (int i = 1, u, v; i <= k; i++) {
        cin >> u >> v;
        cout << solve(u, v) << '\n';
    }
    return 0;
}