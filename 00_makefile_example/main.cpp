#include "message.h"  // Include the custom header file that defines the 'message' class
#include <cstdlib>    // Include the C++ standard library header for general-purpose functions (not used in this code)

using namespace std;  // Allow usage of standard library features without 'std::' prefix (not needed here)

int main() {
    message m;         // Create an instance of the 'message' class
    m.printMessage();  // Call the 'printMessage' method of the 'message' object

    return 0;  // Return 0 to indicate successful program execution
}
