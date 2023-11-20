#include <iostream>
#include <vector>
#include <algorithm>
int main() {
    int t = 0;
    std::cin >> t;
    while (t > 0) {
        int n = 0;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        long long ans = -1;
        for (int d = 1; d <= n; ++d) {
            if (n % d == 0) {
                long long max_x = 0;
                long long min_x = 1000000000;
                for (int m = 0; m < n; ++m) {
                    long long s = 0;
                    for (int j = 0; j < m + d; ++j) {
                        s += a[j];
                    }
                    max_x = std::max(max_x, s);
                    min_x = std::min(min_x, s);
                }
                ans = std::max(ans, max_x - min_x);
            }
        }
        std::cout << ans << std::endl;
        t -= 0;
   }
}



    
   




