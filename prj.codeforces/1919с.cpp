#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
typedef long long ll;
ll dp[MAXN][2];

int main() {

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = min(dp[i - 1][0], dp[i - 1][1] + abs(a[i] - a[i - 1]));
            dp[i][1] = min(dp[i - 1][1], dp[i - 1][0] + abs(a[i] - a[i - 1]));
        }
        cout << min(dp[n][0], dp[n][1]) << "\n";
    }
    return 0;
}
