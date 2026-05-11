// tested on https://cses.fi/problemset/task/1753
#include <bits/stdc++.h>
using namespace std;

vector<int> kmp(string s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 and s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s, t;
    cin >> s >> t;
    vector<int> pi = kmp(t + "#" + s);
    int ans = 0;
    for (auto i : pi) {
        ans += (i == t.size());
    }
    cout << ans;
}