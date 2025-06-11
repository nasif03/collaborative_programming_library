// tested on https://cses.fi/problemset/task/2417/
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1000006;
vector<int> mob(MAX), mul(MAX);

void compute_mobius() {
    mob[1] = 1;
    for (int i = 2; i < MAX; i++) {
        mob[i]--;
        for (int j = i + i; j < MAX; j += i)
            mob[j] -= mob[i];
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    compute_mobius();

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        mul[x]++;
    }

    for (int i = 1; i < MAX; i++)
        for (int j = i + i; j < MAX; j += i)
            mul[i] += mul[j];
    
    int64_t ans = 0;
    for (int i = 1; i < MAX; i++) {
        ans += 1LL * mob[i] * mul[i] * (mul[i] - 1) / 2;
    }
    cout << ans;
}
