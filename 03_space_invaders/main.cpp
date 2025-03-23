#include <iostream>
#include <GLFW/glfw3.h>

// Callback function to be called by GLFW's glfwSetErrorCallback
void error_callback(int error, const char *description) {
    std::cerr << "Error: " << error << description << std::endl;
}

int main() {
    // GLFW will call error_callback when an error occurs
    glfwSetErrorCallback(error_callback);

    // Initialise GLFW library
    if (!glfwInit())
        return -1;

    // OpenGL version at least 4.0. Core profile: explude deprecated features
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Space Invaders", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // Make subsequent OpenGL calls apply to the current context

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Render here
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
