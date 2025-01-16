#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

void renderText(const std::string& msg, float x, float y, float scale, GLFWwindow* glwin)
{
    // TODO: 整合 FreeType 字型繪製
    std::cout << msg << std::endl;
}

int main(int argc, char* argv[])
{
    if (!glfwInit()) {
        std::cerr << "Fail to initilize GLFW" << std::endl;
    }
    // 建立OPENGL 3.3 Core Profile的視窗

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (GLFWwindow* win = glfwCreateWindow(800, 600, "Hello GLFW!", nullptr, nullptr)) {
        glfwMakeContextCurrent(win);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        while(!glfwWindowShouldClose(win)) {
            glClear(GL_COLOR_BUFFER_BIT);

            renderText("Hello GLFW!", 0.0f, 0.0f, 1.0f, win);

            glfwSwapBuffers(win);
            glfwPollEvents();
        }

        glfwDestroyWindow(win);
        glfwTerminate();
    }
    return 0;
}
