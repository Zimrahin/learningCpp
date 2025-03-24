#include <iostream>
#include <GL/glew.h>     // Graphics Library Extension Wrangler
#include <GLFW/glfw3.h>  // Graphics Library Framework

// Callback function to be called by GLFW's glfwSetErrorCallback
void errorCallback(int error, const char *description) {
    std::cerr << "Error: " << error << description << std::endl;
}

int main() {
    // GLFW will call errorCallback when an error occurs
    glfwSetErrorCallback(errorCallback);

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

    // Initialise GLEW: handles function pointer management automatically
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Check OpenGL version
    int glVersion[2];
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
    std::cout << "Renderer used: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    glClearColor(1.0, 0.0, 0.0, 1.0);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);  // Render here
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
