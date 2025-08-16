// tested on https://www.spoj.com/problems/NHAY/en/

#include <bits/stdc++.h>
using namespace std;

using H = array<int64_t, 3>;
mt19937 rng (chrono::steady_clock::now().time_since_epoch().count());
int64_t rand(int64_t l, int64_t r) { return uniform_int_distribution<int64_t>(l, r)(rng); }

const int BASE = rand(300, 1e9);
const int64_t MODS[] = {1000000007, 1000000009};

struct hashed_string {
	vector<int64_t> h[2], p[2];
	
	hashed_string(string s) {
		for (int i = 0; i < 2; i++) {
			p[i].push_back(1);
			h[i].push_back(0);
		}
		for (char c : s) {
			for (int i = 0; i < 2; i++) {
				p[i].push_back(p[i].back() * BASE % MODS[i]);
				h[i].push_back((h[i].back() * BASE + c) % MODS[i]);
			}
		}
	}

	H interval(int l, int r) {
		H res;
        for (int i = 0; i < 2; i++) {
            res[i] = (h[i][r + 1] - h[i][l] * p[i][r + 1 - l]) % MODS[i];
            if (res[i] < 0) res[i] += MODS[i];
        }
		res[2] = r - l + 1;
        return res;
	}

	H concat(H h1, H h2) {
		H res;
		for (int i = 0; i < 2; i++) {
			res[i] = h1[i] * p[i][h2[2]] % MODS[i];
			res[i] = (res[i] + h2[i]) % MODS[i];
		}
		res[2] = h1[2] + h2[2];
		return res;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	string s, t;
	while (cin >> n >> s >> t) {
		hashed_string hs(s), ht(t);
		H hs_full = hs.interval(0, n - 1);
		for (int i = 0; i + n - 1 < t.size(); i++) {
			if (ht.interval(i, i + n - 1) == hs_full) {
				cout << i << "\n";
			}
		}
		cout << "\n";	
	}

	return 0;
}
