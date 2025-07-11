// tested on https://cses.fi/problemset/task/1648/

#include <bits/stdc++.h>
using namespace std;

template <class T>
struct segment_tree {
	int n;
	vector<T> stree;
	function<T(const T &, const T &)> merge;
	T identity = T();
	segment_tree(int n, function<T(const T &, const T &)> merge, T identity) : n(n), merge(merge), identity(identity) {
		stree.resize((n<<2) + 5);
	}
	void build(const vector<T> &arr, int node, int b, int e) {
		if (b == e) {
			stree[node] = arr[b];
			return;
		}
		int mid = (b + e) / 2;
		build(arr, 2 * node, b, mid);
		build(arr, 2 * node + 1, mid + 1, e);
		stree[node] = merge(stree[2 * node], stree[2 * node + 1]);
	}
	segment_tree(const vector<T> &arr, function<T(const T &, const T &)> merge, T identity) : n(arr.size()), merge(merge), identity(identity) {
		stree.resize((n<<2) + 5);
		build(arr, 1, 0, n - 1);
	}
	void modify(int node, int b, int e, int ind, T val, bool upd) {
		if (ind > e or ind < b)
			return;
		if (ind <= b and ind >= e) {
			if (upd) stree[node] = merge(stree[node], val);
			else stree[node] = val;
			return;
		}
		int mid = (b + e) >> 1;
		modify(2 * node, b, mid, ind, val, upd);
		modify(2 * node + 1, mid + 1, e, ind, val, upd);
		stree[node] = merge(stree[2 * node], stree[2 * node + 1]);
	}
	void set(int ind, T val) { modify(1, 0, n - 1, ind, val, 0); }
	void update(int ind, T val) { modify(1, 0, n - 1, ind, val, 1); }

	T query(int node, int b, int e, int l, int r) {
		if (l > e or r < b)
			return identity;
		if (l <= b and r >= e)
			return stree[node];
		int mid = (b + e) >> 1;
		T c1 = query(2 * node, b, mid, l, r);
		T c2 = query(2 * node + 1, mid + 1, e, l, r);
		return merge(c1, c2);
	}
	T query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int64_t> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    segment_tree<int64_t> st(a, [](int64_t a, int64_t b) {return a + b;}, INT64_C(0));
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int k, u; cin >> k >> u;
            st.set(k - 1, u);
        } else {
            int l, r; cin >> l >> r;
            cout << st.query(l - 1, r - 1) << "\n";
        }
    }
}