#define _USE_MATH_DEFINES
#define GL_SILENCE_DEPRECATION

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "defines.h"
#include "buffer/framebuffer.h"

GLFWwindow* initGL(const int width, const int height, const char* title) {
    glfwInit();
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(
        width,
        height,
        title,
        NULL,
        NULL
    );
    if (window == NULL) {
        glfwTerminate();
        exit(1);
    }

    /*glfwSetKeyCallback(window, keyCallback);*/
//    if (glfwRawMouseMotionSupported() == GLFW_TRUE) {
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//#ifdef RAW_MOUSE_INPUT
//        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
//#endif
//    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, width, height);
    glOrtho(0, width, 0, height, Z_NEAR, Z_FAR);
    glPointSize(PIXEL_SCALE);
    return window;
}

typedef struct FrameCounter {
    double frame1;
    double frame2;
} FrameCounter;
FrameCounter frameCounter;

// Wait = 1000ms / n fps
#define FRAME_WAIT 50

void display(GLFWwindow* window) {
    if ((frameCounter.frame1 - frameCounter.frame2) >= FRAME_WAIT) {

        frameCounter.frame2 = frameCounter.frame1;
        glfwSwapBuffers(window);
        glfwSetWindowSize(window, GLSW, GLSH);
    }

    frameCounter.frame1 = glfwGetTime() * 1000;
    glfwPollEvents();
}

int main(int argc, char *argv[]) {
	GLFWwindow* window = initGL(GLSW, GLSH, "CLiR");

    while (!glfwWindowShouldClose(window)) {
        display(window);
    }

    glfwDestroyWindow(window);

    return 0;
}
