#pragma once

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Buffer {
    size_t                width, height;
    std::vector<uint32_t> pixels;
};

struct Sprite {
    size_t                width, height;
    std::vector<uint32_t> pixels;
};

void glSetBufferTextures(Buffer buffer) {
    GLuint bufferTexture;
    glGenTextures(1, &bufferTexture);
    glBindTexture(GL_TEXTURE_2D, bufferTexture);

    // 8-bit RGBA format to represent the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, buffer.width, buffer.height,
                 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, buffer.pixels.data());

    // Nearest neighbourhood (no smoothing)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // If it tries to read beyond the texture bounds, it will use the value at the edges instead
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void glfwSetWindowHints() {
    // OpenGL version at least 4.0. Core profile: explude deprecated features
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void errorCallback(int error, const char *description) {
    std::cerr << "Error: " << error << description << std::endl;
}

void bufferClear(Buffer &buffer, uint32_t colour) {
    std::fill(buffer.pixels.begin(), buffer.pixels.end(), colour);
}

void validateShader(GLuint shader, const char *file = 0) {
    static const unsigned int BUFFER_SIZE = 512;
    char                      buffer[BUFFER_SIZE];
    GLsizei                   length = 0;

    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if (length > 0) {
        std::cerr << "Shader " << shader << "("
                  << (file ? file : "")
                  << ") compile error: " << buffer << std::endl;
    }
}

bool validateProgram(GLuint program) {
    static const GLsizei BUFFER_SIZE = 512;
    GLchar               buffer[BUFFER_SIZE];
    GLsizei              length = 0;

    glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);

    if (length > 0) {
        std::cerr << "Program " << program
                  << " link error: " << buffer << std::endl;
        return false;
    }

    return true;
}

// Create shader for displaying buffer
const char *vertexShader = R"(
    #version 330
    noperspective out vec2 TexCoord;
    
    void main(void){
        TexCoord.x = (gl_VertexID == 2) ? 2.0 : 0.0;
        TexCoord.y = (gl_VertexID == 1) ? 2.0 : 0.0;
        
        gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);
    }
    )";

const char *fragmentShader = R"(
    #version 330  
    uniform sampler2D buffer;
    noperspective in vec2 TexCoord;
    
    out vec3 outColor;
    
    void main(void){
        outColor = texture(buffer, TexCoord).rgb;
    }
    )";

void createVertexShader(GLuint shaderID) {
    GLuint shaderVertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(shaderVertex, 1, &vertexShader, 0);
    glCompileShader(shaderVertex);
    validateShader(shaderVertex, vertexShader);
    glAttachShader(shaderID, shaderVertex);

    glDeleteShader(shaderVertex);
}

void createFragmentShader(GLuint shaderID) {
    GLuint shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader_fp, 1, &fragmentShader, 0);
    glCompileShader(shader_fp);
    validateShader(shader_fp, fragmentShader);
    glAttachShader(shaderID, shader_fp);

    glDeleteShader(shader_fp);
}

uint32_t rgbToUint32(uint8_t r, uint8_t g, uint8_t b) {
    return (r << 24) | (g << 16) | (b << 8) | 255;
}

void checkOpenGLVersion() {
    int glVersion[2];
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
    std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
    std::cout << "Renderer used: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void bufferDrawSprite(Buffer &buffer, const Sprite &sprite, size_t x, size_t y, uint32_t colour) {
    for (size_t xi = 0; xi < sprite.width; ++xi) {
        for (size_t yi = 0; yi < sprite.height; ++yi) {
            if (sprite.pixels[yi * sprite.width + xi] &&
                (sprite.height - 1 + y - yi) < buffer.height &&
                (x + xi) < buffer.width) {
                buffer.pixels[(sprite.height - 1 + y - yi) * buffer.width + (x + xi)] = colour;
            }
        }
    }
}
