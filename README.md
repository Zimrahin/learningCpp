# C++ General Concepts

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


## Passing by Value
- A copy of the argument is passed to the function.
- Modifications inside the function do not affect the original variable.
- Suitable for small or simple data types where copying is inexpensive.

```cpp
#include <iostream>

void modifyValue(int value) {
    value = 100;  // Only the local copy is modified.
}

int main() {
    int a = 10;
    modifyValue(a);
    std::cout << "After modifyValue: " << a << std::endl;  // a remains 10.
    return 0;
}
```

## Passing by Reference
- An alias for the original variable is passed; no copy is made.
- Changes made within the function affect the original variable.
- Efficient for large objects and when modification of the original variable is intended.

```cpp
#include <iostream>

void modifyReference(int &value) {
    value = 100;  // Directly modifies the original variable.
}

int main() {
    int a = 10;
    modifyReference(a);
    std::cout << "After modifyReference: " << a << std::endl;  // a becomes 100.
    return 0;
}
```

## Passing by Constant Reference
- A reference to the original variable is passed, but it is read-only.
- The function can access the variable without copying it but cannot modify it.
- Ideal for large objects when you want to avoid copying and protect against modification.

```cpp
#include <iostream>

void printValue(const int &value) {
    value = 100;  // Error: Cannot modify a constant reference.
    std::cout << "Value: " << value << std::endl;
}

int main() {
    int a = 10;
    printValue(a);
    std::cout << "After printValue: " << a << std::endl;
    return 0;
}
```
<div style="border: 1px solidrgb(243, 127, 18); background-color:rgba(165, 91, 0, 0.77); padding: 10px;">
  The example will <strong>NOT compile</strong> as it attempts to change the value of a constant.
</div>

## Passing by Pointer
- Reference mechanism used within C code and inherited by C++
- Allows modification of the original variable by dereferencing the pointer.
- The pointer can be `nullptr`, so null checks are often necessary.
- Useful passing arrays as arguments.

```cpp
#include <iostream>

void modifyPointer(int *value) {
    if (value != nullptr) {  // Always check for nullptr.
        *value = 100;  // Dereference to modify the original variable.
    }
}

int main() {
    int a = 10;
    modifyPointer(&a);
    std::cout << "After modifyPointer: " << a << std::endl;  // a becomes 100.
    return 0;
}
```

# Object Oriented Programming General Terminology

- Functions declared within a class are known as **Member Functions** (methods in C# and Java).
- Variables declared within a class are known as **Member Variables** or **Data Members**.


## Defining Classes

- Member functions and variables belonging to the class may be placed inside the `{ }`.**Note** the semicolon `;` after the class's closing bracket of the class.

```cpp
class NameOfClass {
    int size;
    void DoSomething() {
        cout << "Something" << endl;
    }
} obj1, obj2; // obj1 and obj2 are optional declarations of instances of NameOfClass
```
- Alternatively, `obj1`, `obj2` can be declared separately
```cpp
class NameOfClass {
    // Class members
};

NameOfClass obj1, obj2; // Declaring objects separately
```
## Defining Member Functions (Methods)
- Member functions may be **defined** outside of the class definition.
    - As long as they are preceded by the class name and scope resolution operator ``::``
```cpp
class NameOfClass {
    // Declaration (prototype) inside the class's definition
    type MemberFunctionName();
}

// Member Function definition outside class definition
type NameOfClass::MemberFunctionName() {
    // Statements
}
```

## Constructor
- A constructor is a special member function (method) that is automatically invoked when an object of the class is instantiated.
- It has the **same name** as the class.
- Equivalent to Python's `__init__()` function.
- Typically used to initialise member variables.

```cpp
class Player {
public:
    int number;
    string name;

    Player(int pNumber, string pName) {
        number = pNumber;
        name = pName;
    }
};
```
- Alternative syntax
    - Instead of assigning values inside the constructor body, member variables can be directly initialised using an **initialiser list**.

```cpp
class Player {
public:
    int number;
    string name;

    Player(int pNumber, string pName) : number(pNumber), name(pName) {}
};
```

## Overloading

- **Function overloading** allows multiple functions with the same name but different parameters.
- The compiler differentiates them based on the **number** or **type** of parameters.

```cpp
#include <iostream>

void print(int x) {
    std::cout << "Integer: " << x << std::endl;
}

void print(double x) {
    std::cout << "Double: " << x << std::endl;
}

void print(std::string x) {
    std::cout << "String: " << x << std::endl;
}

int main() {
    print(10);        // Calls print(int)
    print(3.14);      // Calls print(double)
    print("Hello");   // Calls print(std::string)
    return 0;
}
```

## Access Modifiers or Access Specifier

- Constructors should have `public` access.


| Specifier  | Accessible From Same Class | Accessible From Derived Class | Accessible From Outside Class |
|------------|---------------------------|------------------------------|------------------------------|
| **public**    | ✅ Yes  | ✅ Yes  | ✅ Yes  |
| **protected** | ✅ Yes  | ✅ Yes  | ❌ No  |
| **private**   | ✅ Yes  | ❌ No  | ❌ No  |

```cpp
#include <iostream>

class Example {
public:
    // Python equivalent: self.public_var
    int publicVar = 1;  // Accessible from anywhere

protected:
    // Python equivalent: self._protected_var
    int protectedVar = 2; // Accessible in derived classes

private:
    // Python equivalent: self.__private_var
    int privateVar = 3; // Accessible only in this class
};

class Derived : public Example {
public:
    void show() {
        std::cout << publicVar << std::endl;    // ✅ Accessible
        std::cout << protectedVar << std::endl; // ✅ Accessible
        // std::cout << privateVar << std::endl; // ❌ Error: Not accessible
    }
};

int main() {
    Example obj;
    std::cout << obj.publicVar << std::endl;    // ✅ Accessible
    // std::cout << obj.protectedVar << std::endl; // ❌ Error
    // std::cout << obj.privateVar << std::endl; // ❌ Error
}
```

## Structures (and Function Pointers in C)

- Included in C++ to provide compatibility with C.
- Similar to C++ classes, but inheritance is `public` by default (whereas for classes it's `private` by default).
- Structures in C++ can have member functions (methods), while C structures can't.
    - However, a workaround in C is possible withh **function pointers**.

```c
#include <stdio.h>

typedef struct {
    int x, y;
    void (*print)(struct Point *); // Function pointer inside the struct
} Point;

void printPoint(Point *p) {
    printf("Point(%d, %d)\n", p->x, p->y);
}

int main() {
    Point p = {10, 20, printPoint}; // Assign function pointer
    p.print(&p); // Call the function like a method
    return 0;
}
```

- In C++, with methods, the syntax is simplified to the following.

```cpp
struct Point {
    int x, y;
    void print() { 
        cout << "Point(" << x << ", " << y << ")\n"; 
    }
};
```


# Static vs. Dynamic Objects in C++

```cpp
class Example {
  public:
    Example() {
        std::cout << "Constructor\n";
    }
    ~Example() {
        std::cout << "Destructor\n";
    }
    void show() {
        std::cout << "Hello World!" << std::endl;
    }
};
```

## Static Objects
- **Creation:** Declared normally (**stack** or **global**).
- **Lifetime:** Automatically managed; destroyed at scope exit.
- Method invocation using operator `.`


```cpp
int main() {
    Example obj; // Creation (static)
    obj.show();  // Method invocation using '.'
    // Destructor called automatically
    return 0;
}
```

---

## Dynamic Objects
- **Creation:** Allocated using `new` (**heap**).
- **Lifetime:** Managed manually; must be deallocated using `delete`.
- Method invocation using dereference operator `->`
- Useful when object lifetime needs to extend beyond scope.

```cpp
int main() {
    Example* obj = new Example();  // Creation (dynamic)
    obj->show();                   // Method invocation using '->'
    delete obj;                    // Manual deallocation (calls destructor)
    return 0;
}
```
