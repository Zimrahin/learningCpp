#include <iostream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <GL/glew.h>     // Graphics Library Extension Wrangler
#include <GLFW/glfw3.h>  // Graphics Library Framework

#include "utils.cpp"

#define BUFFER_WIDTH  224
#define BUFFER_HEIGHT 256

int main() {
    // Initialise GLFW library
    if (!glfwInit())
        return -1;
    glfwSetErrorCallback(errorCallback);
    glfwSetWindowHints();

    // Create a windowed mode window and its OpenGL context
    GLFWwindow *window = glfwCreateWindow(BUFFER_WIDTH, BUFFER_HEIGHT, "Space Invaders", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  // Make subsequent OpenGL calls apply to the current context

    // Initialise GLEW: handles function pointer management automatically
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initialising GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    checkOpenGLVersion();

    // Create graphics buffer
    Buffer buffer;
    buffer.width  = BUFFER_WIDTH;
    buffer.height = BUFFER_HEIGHT;
    buffer.pixels.resize(buffer.width * buffer.height);
    bufferClear(buffer, 0);

    // Create texture for presenting buffer to OpenGL
    glSetBufferTextures(buffer);

    // Create Vertex Array Object to generate fullscreen triangle
    GLuint fullscreenTriangleVAO;
    glGenVertexArrays(1, &fullscreenTriangleVAO);

    GLuint shaderID = glCreateProgram();

    createVertexShader(shaderID);
    createFragmentShader(shaderID);
    glLinkProgram(shaderID);

    if (!validateProgram(shaderID)) {
        fprintf(stderr, "Error while validating shader.\n");
        glfwTerminate();
        glDeleteVertexArrays(1, &fullscreenTriangleVAO);
        return -1;
    }

    glUseProgram(shaderID);

    GLint location = glGetUniformLocation(shaderID, "buffer");
    glUniform1i(location, 0);

    // OpenGL setup
    glDisable(GL_DEPTH_TEST);
    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(fullscreenTriangleVAO);

    // Prepare game
    Sprite alien_sprite;
    alien_sprite.width  = 11;
    alien_sprite.height = 8;
    alien_sprite.pixels = {
        0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,  // ..@.....@..
        0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,  // ...@...@...
        0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0,  // ..@@@@@@@..
        0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0,  // .@@.@@@.@@.
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  // @@@@@@@@@@@
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1,  // @.@@@@@@@.@
        1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,  // @.@.....@.@
        0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0   // ...@@.@@...
    };

    uint32_t clearColour = rgbToUint32(0, 128, 0);

    while (!glfwWindowShouldClose(window)) {
        bufferClear(buffer, clearColour);

        bufferDrawSprite(buffer, alien_sprite, 112, 128, rgbToUint32(128, 0, 0));

        glTexSubImage2D(
            GL_TEXTURE_2D, 0, 0, 0,
            buffer.width, buffer.height,
            GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,
            buffer.pixels.data());
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    glDeleteVertexArrays(1, &fullscreenTriangleVAO);

    return 0;
}
