

#include <iostream>
#include <string>
#include <vector>
#include <map>

bool into_vector(std::string s, char c) {
    if ((std::find(s.begin(), s.end(), c)) != s.end()) {
        return true;
    }
    else {
        return false;
    }
}

int count_of_each_letter(char c, std::string s) {
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            count += 1;
        }
    }
    return count;
}


int main()
{
    int n = 0;
    std::cin >> n;
    while (n > 0) {
        std::string s;
        int k = 0;
        std::cin >> s >> k;
        std::string letters;
        for (int i = 0; i < s.length(); i++) {
            if (!into_vector(letters, s[i])) {
                letters += s[i];
            }
        }
        int sum_of_an_pair = 0;
        for (int j = 0; j < letters.length(); j++) {
            sum_of_an_pair += (count_of_each_letter(letters[j], s) % 2);
        }

        if (sum_of_an_pair < k + 1) {
            std::cout << "YES";
        }
        else {
            std::cout << "NO";
        }
    }
    n -= 1;
}



    
   




