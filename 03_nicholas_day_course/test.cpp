#include <iostream>

class AbstractBase {
  public:
    virtual void print() = 0;  // Pure virtual function
};

class Concrete : public AbstractBase {
  private:
    int id;

  public:
    Concrete(int id)
        : id(id) {
    }
    void print() override {  // 'override' is optional but good practice (clarity)
        std::cout << "Overriden function" << std::endl;
    }
};

int main() {
    Concrete c(1);
    c.print();  // Calls the implemented function
    return 0;
}
