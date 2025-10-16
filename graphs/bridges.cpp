#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

const int inf = 1e9;

int n, m, timer;
vector<pii> edges;
vector<vector<pii>> adj;

vector<bool> vis;
vector<int> tin, low, bridges;

void dfs(int v, int p = -1) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    bool par_skip = false;
    for (auto [u, id] : adj[v]) {
        if (u == p && !par_skip) {
            par_skip = true;
            continue;
        }
        if (vis[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v]) bridges.push_back(id);
        }
    }
}

void find_bridges() {
    timer = 0;
    vis.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs(i);
    }
}


void run_case() {
    cin >> n >> m;

    adj.assign(n, vector<pii>());
    edges.clear(), bridges.clear();
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        edges.push_back({u, v});
    }

	find_bridges();
	
	queue<int> q;
	vector<bool> need(m);
	vector<int> par(n, -1), eid(n, -1);
	q.push(0);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto [u, id] : adj[v]) {
			if (par[u] == -1) {
				par[u] = v;
				eid[u] = id;
				q.push(u);
			}
		}
	}
	int x = n - 1;
	while (x) {
		need[eid[x]] = true;
		x = par[x];
	}
	
	vector<int> ans(n, inf);
	sort(bridges.begin(), bridges.end());
    
	for (int i : bridges) {
		if (!need[i]) continue;
		auto [u, v] = edges[i];
		q.push(u), q.push(v);
		ans[u] = min(ans[u], i);
		ans[v] = min(ans[v], i);
	}

	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto [u, id] : adj[v]) {
			if (ans[u] == inf) {
				ans[u] = ans[v];
				q.push(u);
			}
		}
	}

	int qq;
	cin >> qq;
	while (qq--) {
		int c;
		cin >> c;
		--c;
		if (ans[c] == inf) cout << -1 << ' ';
		else cout << ans[c] + 1 << ' ';
	}
	cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) run_case();
    
    return 0;
}
