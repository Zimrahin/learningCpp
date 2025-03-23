#include <iostream>

class Base {
private:
    int id;

public:
    Base() {
        std::cout << "Base Default Constructor\n";
    }
    Base(int id) : id(id) {
        std::cout << "Base Non Default Constructor, id = " << id << std::endl;
    };
};

class Derived : public Base {
public:
    Derived() {
        std::cout << "Derived Default Constructor\n";
    }
    Derived(int id) : Base(id) {
        std::cout << "Derived Non Default Constructor, id = " << id << std::endl;
    };
};

int main() {
    Derived car(3);  // Base class constructor runs first, then derived class
    return 0;
    // Output:
    // Base Non Default Constructor
    // Derived Non Default Constructor
}
