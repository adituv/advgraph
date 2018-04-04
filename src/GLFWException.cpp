#include "GLFWException.h"

void GLFWException::callback(int code, const char* message) {
    GLFWException ex = GLFWException();
    ex.message = message;
    ex.errorCode = code;

    throw ex;
}

const char* GLFWException::what() const noexcept {
    return message;
}
