// tested on https://judge.yosupo.jp/problem/staticrmq

#include <bits/stdc++.h>
using namespace std;

struct sparse_table {
	int n, k;
	vector<vector<int>> st;

	sparse_table(const vector<int> &a) : n(a.size()) {
		k = 33 - __builtin_clz(n);
		st.assign(k, vector<int>(n));

		st[0] = a;
		for (int i = 1; i < k; i++) {
			for (int j = 0; j + (1<<i) - 1 < n; j++) {
				st[i][j] = min(st[i - 1][j], st[i - 1][j + (1<<(i - 1))]);
			}
		}
	} 
	int query(int l, int r) {
		int k = 31 - __builtin_clz(r - l + 1);
		return min(st[k][l], st[k][r - (1<<k) + 1]);
	}
};

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;
	vector<int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	sparse_table st(a);

	while (q--) {
		int l, r;
		cin >> l >> r;
		cout << st.query(l, r - 1) << "\n";
	}

	return 0;
}
