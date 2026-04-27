// https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum

#include <bits/stdc++.h>
using namespace std;

const int N = 300005;

struct dsu_rollback {
    int n;
    vector<int> p, sz;
    stack<tuple<int, int, int64_t>> his;
    //         <op, dst, val>
    
    // problem specific
    vector<int64_t> sum;
    //
    
    dsu_rollback(int _n) : n(_n) {
        p.resize(n);
        sz.resize(n);
        iota(p.begin(), p.end(), 0);
        fill(sz.begin(), sz.end(), 1);

        // problem specific
        sum.resize(n);
        //
    }

    // problem specific
    void add(int x, int val) {
        x = find(x);
        his.push({2, x, sum[x]});
        sum[x] += val;
    }
    int64_t get_sum(int x) {
        x = find(x);
        return sum[x];
    }
    //

    int find(int x) {
        return (x == p[x] ? x : find(p[x]));
    }

    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (sz[y] > sz[x]) {
                swap(x, y);
            }

            his.push({0, y, p[y]});
            his.push({1, x, sz[x]});
            his.push({2, x, sum[x]});

            p[y] = x;
            sz[x] += sz[y];
            sum[x] += sum[y];
            return true;
        }
        return false;
    }

    void rollback(int t) {
        while (int(his.size()) > t) {
            auto [id, x, y] = his.top();
            his.pop();

            if (id == 0) p[x] = y;
            if (id == 1) sz[x] = y;
            if (id == 2) sum[x] = y;
        }
    }
};

struct query {
    int t, u, v, x;
};

dsu_rollback DSU(N);
vector<query> t[4 * N];
int64_t ans[N];

void update(int v, int tl, int tr, int l, int r, query &q) {
    if (l > tr or r < tl) return;
    if (l <= tl and r >= tr) {
        t[v].push_back(q);
        return;
    }
    
    int tm = (tl + tr) / 2;
    update(2 * v, tl, tm, l, r, q);
    update(2 * v + 1, tm + 1, tr, l, r, q);
}

void dfs(int v, int tl, int tr) {
    int sz = DSU.his.size();

    for (auto qq : t[v]) {
        if (qq.t == 1) DSU.join(qq.u, qq.v);
        if (qq.t == 2) DSU.add(qq.v, qq.x);
    }

    if (tl == tr) {
        for (auto qq : t[v]) {
            if (qq.t == 3) {
                ans[tl] = DSU.get_sum(qq.v);
            }
        }
    } else {
        int tm = (tl + tr) / 2;
        dfs(2 * v, tl, tm);
        dfs(2 * v + 1, tm + 1, tr);
    }

    DSU.rollback(sz);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        DSU.sum[i] = a[i];
    }
    
    map<pair<int, int>, int> mp;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            mp[{u, v}] = i;
        }
        if (t == 1) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            int l = mp[{u, v}];
            query cur_q = {1, u, v, -1};
            update(1, 0, q - 1, l, i - 1, cur_q);
            mp[{u, v}] = -1;
        }
        if (t == 2) {
            int v, x;
            cin >> v >> x;
            query cur_q = {2, -1, v, x};
            update(1, 0, q - 1, i, q - 1, cur_q);
        }
        if (t == 3) {
            int v;
            cin >> v;
            query cur_q = {3, -1, v, -1};
            update(1, 0, q - 1, i, i, cur_q);
        }
        if (t != 3) ans[i] = -1;
    }
    for (auto [e, i] : mp) {
        if (i != -1) {
            query cur_q = {1, e.first, e.second, -1};
            update(1, 0, q - 1, i, q - 1, cur_q);
        }
    }

    dfs(1, 0, q - 1);

    for (int i = 0; i < q; i++) {
        if (ans[i] != -1) cout << ans[i] << '\n';
    }
}