#include <bits/stdc++.h>
using namespace std;

//tested on https://cses.fi/problemset/task/1671/

const int inf = 1e9;
using pii = pair<int, int>;
vector<vector<pair<int, int>>> adj;

//            start, adjacency list          , distance      , path
void dijkstra(int s, vector<vector<pii>> &adj, vector<int> &d, vector<int> &p) {
    int n = adj.size();
    d.assign(n, inf);
    p.assign(n, -1);

    d[s] = 0;
    
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, s});
    while (!q.empty()) {
        int d_v = q.top().first;
        int v = q.top().second;
        q.pop();

        if (d_v != d[v])
            continue;

        for (auto [u, len] : adj[v]) {
            if (d[v] + len < d[u]) {
                d[u] = d[v] + len;
                p[u] = v;
                q.push({d[u], u});
            }
        }
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<int> d, p;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    dijkstra(1, adj, d, p);

    for (int i = 1; i <= n; i++)
        cout << d[i] << " ";
}