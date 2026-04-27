// tested on https://judge.yosupo.jp/problem/unionfind

#include <bits/stdc++.h>
using namespace std;

struct dsu {
    vector<int> p, sz;
    int n;

    dsu(int _n) : n(_n) {
        p.resize(n);
        sz.resize(n);
        iota(p.begin(), p.end(), 0);
        fill(sz.begin(), sz.end(), 1);
    }

    int find(int x) {
        return (x == p[x] ? x : (p[x] = find(p[x])));
    }

    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            if (sz[y] > sz[x]) {
                swap(x, y);
            }
            p[y] = x;
            sz[x] += sz[y];
            return true;
        }
        return false;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    dsu DSU(n);
    while (q--) {
        int t, u, v;
        cin >> t >> u >> v;
        if (t == 1) {
            cout << (DSU.find(u) == DSU.find(v)) << '\n';
        } else {
            DSU.join(u, v);
        }
    }
}