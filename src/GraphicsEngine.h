#ifndef GRAPHICSENGINE_H_
#define GRAPHICSENGINE_H_

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLFWException.h"

// Singleton class for the graphics engine.  Only supports a single window.
class GraphicsEngine {
  private:
    GLFWwindow* window;
    GLuint program;

    static GraphicsEngine* instance;
  public:
    virtual ~GraphicsEngine();

    static GraphicsEngine* getInstance() noexcept;
    static void destroyInstance();

    void InitWindow(int, int, const char*);
    void AttachShader(GLenum, const char*);
    void UpdateProgram();
    void RunLoop();
};

#endif
