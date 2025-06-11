// tested on https://judge.yosupo.jp/problem/zalgorithm
#include <bits/stdc++.h>
using namespace std;

vector<int> zfunction(string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r)
            z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n and s[i] == s[i + z[i]])
            z[i]++;
        if (i + z[i] > r)
            l = i, r = i + z[i];
    }
    return z;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    vector<int> z = zfunction(s);
    z[0] = s.size();
    for (auto i : z) cout << i << " ";
}