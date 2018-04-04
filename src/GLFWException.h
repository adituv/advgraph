#ifndef GLFWEXCEPTION_H_
#define GLFWEXCEPTION_H_

#include <exception>

class GLFWException : public std::exception {
  private:
    const char* message;
    int errorCode;
  public:
    static void callback(int, const char*);
    int getErrorCode() const noexcept;
    const char* what() const noexcept override;
};

#endif

