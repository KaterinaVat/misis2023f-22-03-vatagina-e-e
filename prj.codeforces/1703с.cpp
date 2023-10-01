#include <iostream>
#include <vector>
#include <string>


int main() {
	int t, n, b;
	std::string str;


	std::cin >> t;
	while (t > 0) {

		std::cin >> n;
		int temp;

		//заполнение массива
		std::vector<int> a_i;
		for (int i = 0; i < n; i++) {
			std::cin >> temp;
			a_i.push_back(temp);
		}

		//буквы
		for (int i = 0; i < n; i++) {
			std::cin >> b;
			std::cin >> str;

			for (int j = 0; j < str.length(); j++) {
				if (str[j] == 'U') {
					a_i[i] -= 1;
					if (a_i[i] < 0) {
						a_i[i] = 9;
					}
					if (a_i[i] > 9) {
						a_i[i] = 0;
					}
				}
				else {
					a_i[i] += 1;
					if (a_i[i] < 0) {
						a_i[i] = 9;
					}
					if (a_i[i] > 9) {
						a_i[i] = 0;
					}
				}
			}
		}

		for (int i = 0; i < n; i++) {
			std::cout << a_i[i] << ' ';
		}
		std::cout << std::endl;
		t -= 1;
	}
}