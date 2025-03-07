#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Gem/Core/Clock.h>
#include <Gem/Core/GemEngine.h>

int main() {
	// Initialize GLFW
	Gem::GemEngine::getInstance().init();

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current
	glfwMakeContextCurrent(window);
	// Load OpenGL functions

	// Create a timer
	Gem::Clock clock;
	clock.logFPS(1); // Log FPS every second

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		

		// Render here
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Swap front and back buffers
		glfwSwapBuffers(window);
		
		// Poll for and process events
		glfwPollEvents();
		
		clock.update(0); // Cap FPS to 60
				
	}

	// Terminate GLFW
	Gem::GemEngine::getInstance().shutdown();

	return 0;
}