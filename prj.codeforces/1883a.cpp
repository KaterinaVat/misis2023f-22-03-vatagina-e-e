#include <iostream>
#include <cmath>

int main() {
    int n;

    std::cin >> n;
    while (n > 0) {
        int number;
        int time;
        std::cin >> number;
        int n1, n2, n3,n4;
        n1 = number / 1000;
        n2 = (number / 100) % 10;
        n3 = (number % 100) / 10;
        n4 = (number % 10);

        if (n1 == 0) {
            n1 = 10;
        }
        if (n2 == 0) {
            n2 = 10;
        }
        if (n3 == 0) {
            n3 = 10;
        }
        if (n4 == 0) {
            n4 = 10;
        }

        time = abs(n1 - 1) + abs(n2 - n1) + abs(n3 - n2) + abs(n4 - n3)+4;
        std::cout << time << std::endl;
        n--;
    }
}