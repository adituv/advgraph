#include "GraphicsEngine.h"
#include "GLFWException.h"

#include <fstream>
#include <vector>

GraphicsEngine* GraphicsEngine::instance = nullptr;

GraphicsEngine::~GraphicsEngine() {
    glfwSetErrorCallback(nullptr);
    glfwDestroyWindow(instance->window);
    glfwTerminate();
}

GraphicsEngine* GraphicsEngine::getInstance() noexcept {
    if (!instance) {
        instance = new GraphicsEngine();
    }

    return instance;
}

void GraphicsEngine::destroyInstance() {
    delete instance;
}

void GraphicsEngine::InitWindow(int width, int height, const char* title) {
    glfwSetErrorCallback(GLFWException::callback);
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glClearColor(0.2f, 0.4f, 0.6f, 0.0f);
    glClearDepth(1.0f);

    program = glCreateProgram();
}

void GraphicsEngine::AttachShader(GLenum shaderType, const char* path) {
    std::ifstream file;
    std::vector<char> fileContents;
    GLuint shader;
    int fileSize;
    const char* fileData;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    file.open(path);

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    fileContents = std::vector<char>(fileSize);
    file.read(fileContents.data(), fileSize);

    shader = glCreateShader(shaderType);
    fileData = fileContents.data();
    glShaderSource(shader, 1,
                   &fileData,
                   &fileSize);
    glCompileShader(shader);
    glAttachShader(program, shader);
}

void GraphicsEngine::UpdateProgram() {
    glLinkProgram(program);
    glUseProgram(program);
}

void GraphicsEngine::RunLoop() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
