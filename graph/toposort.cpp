#include <iostream>
#include <queue>
using namespace std;
const int N = 1e4 + 5;
int n, deg[N];
vector<int> G[N], ans;
queue<int> Q;
void toposort() {
    for (int i = 1; i <= n; i++)
        if (!deg[i]) {
            ans.push_back(i);
            Q.push(i);
        }
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int v : G[u])
            if (!--deg[v]) {
                ans.push_back(v);
                Q.push(v);
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
            G[i].push_back(u);
        }
    toposort();
    for (auto i : ans) cout << i << ' ';
    return 0;
}