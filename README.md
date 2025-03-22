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
    int    number;
    string name;

    Player(int pNumber, string pName) : number(pNumber), name(pName) {};
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
    print(10);       // Calls print(int)
    print(3.14);     // Calls print(double)
    print("Hello");  // Calls print(std::string)
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
    int protectedVar = 2;  // Accessible in derived classes

  private:
    // Python equivalent: self.__private_var
    int privateVar = 3;  // Accessible only in this class
};

class Derived : public Example {
  public:
    void show() {
        std::cout << publicVar << std::endl;     // ✅ Accessible
        std::cout << protectedVar << std::endl;  // ✅ Accessible
        // std::cout << privateVar << std::endl; // ❌ Error: Not accessible
    }
};

int main() {
    Example obj;
    std::cout << obj.publicVar << std::endl;  // ✅ Accessible
    // std::cout << obj.protectedVar << std::endl; // ❌ Error
    // std::cout << obj.privateVar << std::endl; // ❌ Error
}
```

## Encapsulation
  
- Encapsulation is the practice of **hiding an object's internal state** (its member variables) and **controlling access** to that state through **member functions (methods)**.
- Declare member variables as **`private`**.  
- Provide **getter** and **setter** functions (or other interfaces) to manipulate and retrieve state.
- **Mutators (Setters)**  
     - **Allow changes** to the object’s state.  
     - Typically non-`const`.  

- **Accessors (Getters)**  
     - **Do not modify** the object’s state.  
     - Often declared **`const`** to ensure they cannot alter member variables.  

```cpp
class Example {
  private:
    int data;  // Encapsulated member

  public:
    // Setter (mutator)
    void setData(int d) {
        if (d > 0)
            data = d;
    }

    // Getter (accessor)
    int getData() const {
        return data;
    }
};
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
    void (*print)(struct Point *);  // Function pointer inside the struct
} Point;

void printPoint(Point *p) {
    printf("Point(%d, %d)\n", p->x, p->y);
}

int main() {
    Point p = { 10, 20, printPoint };  // Assign function pointer
    p.print(&p);                       // Call the function like a method
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


## Static vs. Dynamic Objects in C++

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

### Static Objects
- **Creation:** Declared normally (**stack** or **global**).
- **Lifetime:** Automatically managed; destroyed at scope exit.
- Method invocation using operator `.`


```cpp
int main() {
    Example obj;  // Creation (static)
    obj.show();   // Method invocation using '.'
    // Destructor called automatically
    return 0;
}
```

---

### Dynamic Objects
- **Creation:** Allocated using `new` (**heap**).
- **Lifetime:** Managed manually; must be deallocated using `delete`.
- Method invocation using dereference operator `->`
- Useful when object lifetime needs to extend beyond scope.

```cpp
int main() {
    Example* obj = new Example;  // Creation (dynamic)
    obj->show();                   // Method invocation using '->'
    delete obj;                    // Manual deallocation (calls destructor)
    return 0;
}
```

### Anonymous Objects
- Create objects on the fly without storing them in a named variable.
- Typically used for immediate function calls.

```cpp
#include <iostream>

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

// Function that takes a pointer to an Example object.
void display(Example *ex) {
    if (ex) {
        ex->show();
        delete ex;  // Clean up the dynamically allocated object.
    }
}

int main() {
    Example().show();        // Create an anonymous object (static) and call its method immediately.
    display(new Example);  // Create an anonymous (dynamic) object and pass its pointer to the function.
    // Output
    // Constructor
    // Hello World!
    // Destructor
    // Constructor
    // Hello World!
    // Destructor
    return 0;
}
```



## Inheritance

- **Syntax:** Use a colon (`:`) after the class name followed by the access specifier (`public`, `protected`, `private`) and the base class name.
- **Multiple inheritance** (a class can inherit from more than one base class) is possible in C++, but its use is **not recommended**.
    - **Naming Conflicts:** Same member names in different bases can cause ambiguity.
    - **Diamond Problem:** Ambiguity arises when two base classes inherit from the same ancestor.
  
```cpp
class Base {
  public:
    void show() {
        std::cout << "Base\n";
    }
};

class Derived : public Base {
    // Inherits public members of Base as public
};

```

### Abstract Member Functions and Classes
- **Abstract Member Function (*virtual*):**
  - Declared with `= 0` (pure **virtual** function).
  - No implementation in the base class.
  - Forces derived classes to provide an **override**.

- **Abstract Class:**
  - Contains at least one pure **virtual** function.
  - Cannot be instantiated directly.
  - Serve as a blueprint for derived classes.
  - **Purpose:** Enforce that certain methods are implemented in derived classes.
  
```cpp
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
```

# Project organisation

- **Header file (`.h`)**: Contains the class definition (the **interface**) and method declarations.  
- **Source file (`.cpp`)**: Contains the **implementation** (method definitions).
- **Maintainability**: Changes to implementation don’t force recompilation of all files that include the header (when used properly).
- **File Naming**: By convention, each class has its own `.h` and `.cpp` file, named after the class (e.g., `Player.h` and `Player.cpp`).
- See `03_nicholas_day_corurse/project_organisation` for an example



## Constructors and Inheritance


```cpp
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
```
- When a derived class is instantiated, its constructor **implicitly calls** the default constructor of the base class.
- The **base class constructor executes first**, followed by the derived class constructor.
- In this example, the **default** constructor of the base class is called first.

    ```cpp
    class Derived : public Base {
    public:
        Derived() {
            std::cout << "Derived Default Constructor\n";
        }
        Derived(int id) {
            std::cout << "Derived Non Default Constructor, id = " << id << std::endl;
        };
    };

    int main() {
        Derived car(3);  // Base class constructor runs first, then derived class
        return 0;
        // Output:
        // Base Default Constructor
        // Derived Non Default Constructor, id = 3
    }
    ```
- To call the **non default** constructor, (and thus assign a value to the private parameter id).
    - The parent's constructor name follows the **colon** `:` after the child's constructor.
- Arguments can be passed this way from the child to the parent's constructor.

    ```cpp
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
        // Base Non Default Constructor, id = 3
        // Derived Non Default Constructor, id = 3
    }
    ```
    - In Python, the same effect can be achieved using `super()`, which calls the constructor of the base class. 
        ```python
        class Base:
            def __init__(self, id):
                self.id = id
                print(f"Base Non-Default Constructor, id = {id}")


        class Derived(Base):
            def __init__(self, id):
                super().__init__(id)  # Calls the constructor of the base class
                print(f"Derived Non-Default Constructor, id = {id}")

        obj = Derived(3)
        # Output
        # Base Non-Default Constructor, id = 3
        # Derived Non-Default Constructor, id = 3
        ```
