#include "GraphicsEngine.h"

int main(void)
{
    GraphicsEngine* Graphics = GraphicsEngine::getInstance();
    Graphics->InitWindow(640, 480, "Hello World!");
    Graphics->AttachShader(GL_VERTEX_SHADER, "shaders/simple.vert");
    Graphics->AttachShader(GL_FRAGMENT_SHADER, "shaders/simple.frag");
    Graphics->UpdateProgram();

    Graphics->RunLoop();

    GraphicsEngine::destroyInstance();
}
