#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string who_wins(int a, int b) {
    vector<int> dp(b + 1, 0);
    for (int i = 0; i <= a; ++i) {
        for (int j = 0; j <= b; ++j) {
            if (j >= i) {
                dp[j] = max(dp[j], (j - i >= 0 ? dp[j - i] : 0) + i);
            }
            else {
                dp[j] = max(dp[j], (j + i <= b ? dp[j + i] : 0) + i);
            }
        }
    }
    return dp[b] >= a ? "Alice" : "Bob";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << who_wins(a, b) << endl;
    }
    return 0;
}
