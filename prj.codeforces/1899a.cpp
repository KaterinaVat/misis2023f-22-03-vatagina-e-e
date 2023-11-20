#include <iostream>
int main() {
    int n;
    std::cin >> n;
    int number = 0;
    while (n >0){
        std::cin >> number;
        if (number % 3 == 0) {
            std::cout << "Second" << std::endl;

        }
        else {
            std::cout << "First" << std::endl;
        }

        n -= 1;
    }
}


    
   




