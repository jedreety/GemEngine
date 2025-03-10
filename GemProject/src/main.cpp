
#include <iostream>

#include <glm/glm.hpp>

#include <Gem/Core/GemEngine.h>
#include <Gem/Core/Clock.h>
#include <Gem/Core/Logger.h>

#include <Gem/Window/Window.h>
#include <Gem/Graphics/camera.h>

#include <Gem/Graphics/shader.h>
#include <Gem/Graphics/textures/tex_2D.h>

#include <Gem/Graphics/shapes/sphere.h>
#include <Gem/Graphics/shapes/cube.h>

int main() {

	Gem::Logger::debug("This is a debug log. Debug level: {}", 123);
	Gem::Logger::info("This is an info log with string: {}", "GemEngine starting...");
	Gem::Logger::warning("This is a warning log, watch out!");
	Gem::Logger::error("This is an error log, handle carefully.");

	// Initialize GLFW
	Gem::GemEngine::getInstance().init();
	Gem::Window window(800, 600, "GemEngine Window");

	// Create a timer
	Gem::Clock clock;
	clock.logFPS(1); // Log FPS every second

	// Create default shader for the sphere
	Gem::Graphics::Shader shader;
	shader.set_path("src/"); // Set the path where shader files are located

	// Create position-based color shader for the cube
	Gem::Graphics::Shader positionColorShader;
	positionColorShader.set_path("src/"); // Set the path where shader files are located

	try {
		// Load default shader
		shader.add_shader(GL_VERTEX_SHADER, "default.vert"); // Add vertex shader
		shader.add_shader(GL_FRAGMENT_SHADER, "default.frag"); // Add fragment shader
		shader.link_program(); // Link shaders into a shader program
		
		// Load position color shader
		positionColorShader.add_shader(GL_VERTEX_SHADER, "position_color.vert"); // Add vertex shader
		positionColorShader.add_shader(GL_FRAGMENT_SHADER, "position_color.frag"); // Add fragment shader
		positionColorShader.link_program(); // Link shaders into a shader program
	}
	catch (const std::exception& e) {
		std::cerr << "Shader compilation/linking failed: " << e.what() << std::endl;
		exit(EXIT_FAILURE); // Exit if shaders fail to compile/link
	}

	Gem::Graphics::Shapes::Sphere player_sphere(1); // Small sphere representing the player
	Gem::Graphics::Shapes::Cube cube(1); // Cube for the ground

	Gem::Graphics::Texture2D texture; // Load a texture for the player sphere
	texture.set_path("src/");
	texture.set_mag_filter(GL_NEAREST);
	texture.load_texture("dirt.png");
	texture.bind(0);

	shader.add_uniform_location("texture_diffuse");
	shader.add_uniform_location("modelMatrix");
	positionColorShader.add_uniform_location("modelMatrix");
	glm::mat4 model = glm::mat4(1.0f); // Initialize model matrix

	// Loop until the user closes the window
	while (Gem::GemEngine::getInstance().isRunning()) {

		clock.update(0); // Cap FPS to 60
		window.update();

		// Render sphere with default shader
		shader.activate();
		shader.set_uniform_matrix("modelMatrix", glm::value_ptr(model), 1, GL_FALSE, GL_FLOAT_MAT4);
		shader.set_uniform("texture_diffuse", 0);
		player_sphere.render();
		
		// Render cube with position color shader
		positionColorShader.activate();
		positionColorShader.set_uniform_matrix("modelMatrix", glm::value_ptr(model), 1, GL_FALSE, GL_FLOAT_MAT4);
		cube.render();

		window.render();

	}

	// Terminate GLFW
	Gem::GemEngine::getInstance().shutdown();

	return 0;
}