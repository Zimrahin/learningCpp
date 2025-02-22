// https://codeforces.com/contest/2044/problem/A
#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;
    if (t < 1 || t > 99) return 1;

    // Can't use array<int, t> because the size must be set at compile time
    std::vector<int> output(t);

    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n;
        if (n < 2 || n > 100) return 1;
        output[i] = n - 1;
    }

    for (int out : output) {
        std::cout << out << std::endl;
    }

    return 0;
}
