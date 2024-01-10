#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 5005;
typedef long long ll;
ll dp[MAXN][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '+') {
                dp[i + 1][0] = min(dp[i + 1][0], dp[i][0] + i + 1);
                dp[i + 1][1] = min(dp[i + 1][1], dp[i][1] + i + 1);
            }
            else {
                dp[i + 1][0] = min(dp[i + 1][0], dp[i][1] + i + 1);
                dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + i + 1);
            }
        }
        cout << min(dp[n][0], dp[n][1]) << "\n";
    }
    return 0;
}
