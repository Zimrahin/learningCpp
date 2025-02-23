// https://codeforces.com/problemset/problem/231/A
#include <iostream>

int main() {
    int count = 0, n;
    std::cin >> n;
    while (n--) {
        int ones = 0, col = 3, x;
        while (col--) {
            std::cin >> x;  // std::cin handles spaces
            if (x == 1)
                ones++;
        }
        if (ones >= 2)
            count++;
    }
    std::cout << count << std::endl;
    return 0;
}
