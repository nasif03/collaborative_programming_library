#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p;
    DSU(int n) : p(n, -1) {}
    bool same_set(int a, int b) {
        return find(a) == find(b);
    }
    int size(int x) {
        return -p[find(x)];
    }
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    int comps = n, mx = 1;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (dsu.join(a, b)) comps--;
        mx = max(mx, max(dsu.size(a), dsu.size(b)));
        cout << comps << " " << mx << "\n";
    }
}