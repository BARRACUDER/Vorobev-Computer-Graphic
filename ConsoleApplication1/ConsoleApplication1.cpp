#include <iostream>
#include "GL\glew.h"
#include"GLFW\glfw3.h"
int main()
{
	if (!glfwInit()) {
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(512, 512, "MainWindow", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	GLenum ret = glewInit();
	if (GLEW_OK != ret) {
		return 1;
	}
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.8f, 0.2f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glColor3f(0.3, 0.6, 0.1);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);

        glColor3f(0.3, 0.6, 0.1);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
        glEnd();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}