#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "model.h"

#define FALSE 0

GLuint loadShader(GLenum shaderType, const char* path);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);
    glfwShowWindow(window);

    glClearColor(0.2f, 0.4, 0.6f, 0.0f);
    glClearDepth(1.0f);

    GLuint vs = loadShader(GL_VERTEX_SHADER, "shaders/simple.vert");
    GLuint fs = loadShader(GL_FRAGMENT_SHADER, "shaders/simple.frag");

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    // Temporary: render a triangle
    Vector3 vertices[3] = { { 0.0f,  0.0f, 0.0f},
                            { 0.5f, -0.5f, 0.0f},
                            {-0.5f, -0.5f, 0.0f} };
    Color vColors[3] = { { 1.0f, 0.0f, 0.0f, 1.0f },
                         { 0.0f, 1.0f, 0.0f, 1.0f },
                         { 0.0f, 0.0f, 1.0f, 1.0f }};
    Model triangle = { vertices, vColors, 1,
                       {0,0,0}, {0,0,0}, 1.0f
                     };

    GLuint vLoc = glGetAttribLocation(program, "vPos");
    GLuint cLoc = glGetAttribLocation(program, "vColor");
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(vLoc);
    glEnableVertexAttribArray(cLoc);

    GLuint buffers[2];
    glGenBuffers(2, buffers);

    GLuint vbo_vertices = buffers[0];
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, 4*3*3, triangle.vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(vLoc, 3, GL_FLOAT, FALSE, 0, 0);

    GLuint vbo_colors = buffers[1];
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, 4*4*3, triangle.vColors, GL_STATIC_DRAW);
    glVertexAttribPointer(cLoc, 4, GL_FLOAT, FALSE, 0, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteBuffers(2, buffers);
    glDeleteVertexArrays(1, &vao);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

GLuint loadShader(GLenum shaderType, const char* path) {
    FILE* fp;
    long lSize;
    int iSize;
    char* buffer;
    GLuint shader;
    GLuint ret = 0;

    fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "File \"%s\" not found.\n", path);
        goto onError;
    }

    fseek(fp, 0L, SEEK_END);
    lSize = ftell(fp);
    rewind(fp);

    iSize = (int) lSize;

    buffer = calloc(1, lSize+1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed for \"%s\"", path);
        goto onError;
    }

    if (fread(buffer, lSize, 1, fp) != 1) {
        fprintf(stderr, "Read failed for \"%s\"", path);
        goto onError;
    }

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, (const char* const*)&buffer, &iSize);
    glCompileShader(shader);
    ret = shader;

cleanup:
    fclose(fp);
    free(buffer);
    return ret;

onError:
    ret = 0;
    goto cleanup;
}
