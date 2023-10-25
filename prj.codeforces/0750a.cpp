#include <iostream>


int main() {
    int n, k;
    std::cin >> n >> k;

    int left = 0;
    int right = n;

    while (left < right) {
        int mid = (right+left+1) / 2;
        int total_time = (5 * (mid * (mid + 1)) / 2) + k;

        if (total_time <= 240) {
            left = mid;
        }
        else {
            right = mid - 1;
        }
    }

    std::cout << left;

}
