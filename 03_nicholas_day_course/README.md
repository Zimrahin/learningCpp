# Notes on Nicholas Day's C++ course

## Namespaces 
- A **namespace** is an identified declarative region that avoids naming conflicts.
- Identifiers within a namespace are accessed using the **scope operator `::`**.
- The **using** keyword avoids having to scope each object within the namespace

```cpp
#include <iostream>

namespace myFirstNamespace {
    int a = 10;
}

namespace mySecondNamespace {
    int a = 12;
}

int main() {
    int c = myFirstNamespace::a + mySecondNamespace::a;
    std::cout << c << std::endl;

    using myFirstNamespace::a;
    c = a + mySecondNamespace::a;
    std::cout << c << std::endl;

    return 0;
}
```

## Insertion and extraction operator
- Data is output using the **insertion operator `<<`**.
- Data is retrieved using the **extraction operator `>>`**
- **cout** is an object of the **ostream** class

```cpp
#include <iostream>

int main() {
    int c;
    std::cin >> c;
    std::cout << c << std::endl;
    return 0;
}
```

