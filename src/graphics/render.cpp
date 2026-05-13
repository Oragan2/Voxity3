extern "C" {
	#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#include <iostream>

// Callback to resize the viewport if the user scales the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int initWindow() {
    // 1. Initialize GLFW
    if (!glfwInit()) return -1;

    // Set OpenGL version to 4.6 (Core Profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2. Create Window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Voxitry Engine", NULL, NULL);
    if (window == nullptr) {
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 3. Load OpenGL functions via GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -3;
    }

    // 4. Main Render Loop
    while (!glfwWindowShouldClose(window)) {
        // Input Handling
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // Rendering Logic
        glClearColor(0.1f, 0.1f, 0.14f, 1.0f); // Dark background for your devlog
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- Your Physics & Voxel Rendering calls will go here ---

        // Swap buffers (Double Buffering) and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
