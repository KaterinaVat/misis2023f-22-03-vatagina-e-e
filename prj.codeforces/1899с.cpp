#include <vector>
#include <iostream>

int main() {
    int l = 0;
    std::vector<int> arr(l);

    std::cin >> l;

    for (int i = 0; i < l; i++) {
        std::cin >> arr[i];
    }

    int max_sum = -100000;
    for (int i = 0; i < l-1; i++) {
        curent_sum = arr[i];
        for (int j = i + 1; j < l; j++) {
            if (arr[j-1] % 2 != arr[j] % 2) {
                curent_sum += arr[j];
            }
            else {
                curent_sum = 0;
            }
            if (curent_sum > max_sum) {
                max_sum = cur_sum;
            }
           }
    }
    std::cout << max_sum;
}

    
   




