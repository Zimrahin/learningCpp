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

