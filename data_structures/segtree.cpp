// tested on https://cses.fi/problemset/task/1648/

#include <bits/stdc++.h>
using namespace std;

struct segment_tree {
	typedef int64_t T;
	T identity = 0;	
	T merge(T a, T b) { return (a + b); }

	int n;
	vector<T> t;
	segment_tree(int n) {
		t.assign(2 * n, identity);
	}
	segment_tree(const vector<T> &a) {
		n = a.size();
		t.assign(2 * n, identity);
		build(a, 0, 0, n - 1);
	}
	void build(const vector<T> &a, int v, int tl, int tr) {
		if (tl == tr) {
			t[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(a, v + 1, tl, tm);
		build(a, v + 2 * (tm - tl + 1), tm + 1, tr);
		t[v] = merge(t[v + 1], t[v + 2 * (tm - tl + 1)]);
	}
	T _query(int v, int tl, int tr, int l, int r) {
		if (l > tr or r < tl) return identity;
		if (l <= tl and r >= tr) return t[v];
		int tm = (tl + tr) / 2;
		T lc = _query(v + 1, tl, tm, l, r);
		T rc = _query(v + 2 * (tm - tl + 1), tm + 1, tr, l, r);
		return merge(lc, rc);
	}
	T query(int l, int r) {
		return _query(0, 0, n - 1, l, r);
	}
	void _update(int v, int tl, int tr, int pos, T val, bool f) {
		if (tl == tr) {
			if (f) t[v] = val;
			else t[v] = merge(t[v], val);
			return;
		}
		int tm = (tl + tr) / 2;
		if (pos <= tm) _update(v + 1, tl, tm, pos, val, f);
		else _update(v + 2 * (tm - tl + 1), tm + 1, tr, pos, val, f);
		t[v] = merge(t[v + 1], t[v + 2 * (tm - tl + 1)]);
	}
	void update(int pos, T val, bool overwrite) {
		_update(0, 0, n - 1, pos, val, overwrite);
	}
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
	cin >> n >> q;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

	segment_tree st(a);
	int t, u, v;
	while (q--) {
		cin >> t >> u >> v;
		if (t == 0) st.update(u, v, false);
		else cout << st.query(u, v - 1) << '\n';
	}
}