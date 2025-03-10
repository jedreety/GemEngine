#pragma once

#include <../../GemCore/include-protected/function_overload.h>

#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <Gem/Graphics/shader.h>
#include <../../GemWindow/include-protected/Inputs.h>
#include <Gem/Graphics/buffer.h>

namespace Gem {

    namespace Graphics {

        /**
         * @brief Camera class for handling camera movements and view/projection matrices.
         *
         * The Camera class encapsulates the functionality required to control the camera in a 3D environment.
         * It handles user input for movement and orientation, and provides view and projection matrices for rendering.
         */
        class Camera {
        public:
            /**
             * @brief Constructs a Camera object with default parameters.
             *
             * Initializes camera position, orientation, and other parameters to default values.
             */
            Camera() noexcept;

            /**
             * @brief Constructs a Camera object with a specific position.
             *
             * @param position The initial position vector for the camera.
             */
            explicit Camera(const glm::vec3& position) noexcept;

            /**
             * @brief Constructs a Camera object with a specific field of view (FOV).
             *
             * @param fov The field of view in degrees.
             */
            explicit Camera(float fov) noexcept;

            /**
             * @brief Constructs a Camera object with specific position and field of view.
             *
             * @param position The initial position vector for the camera.
             * @param fov The field of view in degrees.
             */
            Camera(const glm::vec3& position, float fov) noexcept;

            /**
             * @brief Constructs a Camera object with full customization.
             *
             * @param position The initial position vector for the camera.
             * @param fov The field of view in degrees.
             * @param speed The movement speed of the camera.
             * @param sensitivity The mouse sensitivity for camera rotation.
             */
            Camera(const glm::vec3& position, float fov, float speed, float sensitivity) noexcept;

            /**
             * @brief Sets the uniform locations for the view and projection matrices in the shader.
             *
             * @param shader Pointer to the Shader object.
             */
            void set_matrix_location(Gem::Graphics::Shader* shader) const;

            /**
             * @brief Sets the Camera dimensions.
             *
             * @param width Camera width in pixels.
             * @param height Camera height in pixels.
             */
            void set_dimensions(int width, int height) noexcept;

            /**
             * @brief Sets the camera's position in the world.
             *
             * @param position The position vector.
             */
            void set_position(const glm::vec3& position) noexcept;

            /**
             * @brief Sets the movement speed of the camera.
             *
             * @param speed Movement speed.
             */
            void set_speed(float speed) noexcept;

            /**
             * @brief Sets the mouse sensitivity for camera rotation.
             *
             * @param sensitivity Mouse sensitivity.
             */
            void set_sensitivity(float sensitivity) noexcept;

            /**
             * @brief Sets the field of view (FOV) for the projection matrix.
             *
             * @param fov Field of view in degrees.
             */
            void set_fov(float fov) noexcept;

            /**
             * @brief Gets the camera's current position.
             *
             * @return The position vector.
             */
            [[nodiscard]] glm::vec3 get_position() const noexcept;

            /**
             * @brief Gets the camera's current orientation.
             *
             * @return The orientation vector (forward direction).
             */
            [[nodiscard]] glm::vec3 get_orientation() const noexcept;

            /**
             * @brief Gets the camera's current field of view.
             *
             * @return The field of view in degrees.
             */
            [[nodiscard]] float get_fov() const noexcept;

            /**
             * @brief Updates the camera based on user input and elapsed time.
             *
             * This method processes inputs and updates the camera matrices in one call.
             * It should be called once per frame in the game loop.
             *
             * @param window Pointer to the GLFW window.
             * @param inputs Pointer to the Inputs object.
             * @param deltaTime Time elapsed since the last frame in seconds.
             */
            void update(GLFWwindow* window, float deltaTime);

            /**
             * @brief Equality operator.
             *
             * Compares two Camera objects based on their positions and orientations.
             *
             * @param other The other Camera object to compare with.
             * @return True if both cameras have the same position and orientation, false otherwise.
             */
            bool operator==(const Camera& other) const noexcept;

            /**
             * @brief Inequality operator.
             *
             * Compares two Camera objects based on their positions and orientations.
             *
             * @param other The other Camera object to compare with.
             * @return True if the cameras have different positions or orientations, false otherwise.
             */
            bool operator!=(const Camera& other) const noexcept;

        private:

            /**
             * @brief Initializes the camera with the required attributes.
             *
             * Must be called after setting the necessary attributes like window dimensions and position.
             *
             * @throws std::runtime_error if required attributes are not set.
             */
            void init();

            /**
             * @brief Updates and sends the view and projection matrices to the shader.
             *
             * Calculates the view and projection matrices based on the camera's current state.
             */
            void update_matrices() const;

            /**
             * @brief Handles camera input processing.
             *
             * Processes both keyboard and mouse inputs to update the camera's position and orientation.
             *
             * @param inputs Pointer to the Inputs object.
             */
            void process_inputs(GLFWwindow* window, float deltaTime);

            /**
             * @brief Checks if the required attributes are set before initialization.
             *
             * @return True if attributes are set, false otherwise.
             */
            [[nodiscard]] bool are_attributes_set() const noexcept;

            /**
             * @brief Processes keyboard inputs to move the camera.
             *
             * @param inputs Pointer to the Inputs object
             */
            void process_keyboard_input(float deltaTime);

            /**
             * @brief Processes mouse inputs to rotate the camera.
             *
             * @param inputs Pointer to the Inputs object
             */
            void process_mouse_input(GLFWwindow* window);

        private:

            glm::vec3 position_{ 0.0f, 0.0f, 0.0f };        ///< Camera position.
            glm::vec3 orientation_{ 0.0f, 0.0f, -1.0f };    ///< Camera forward direction.
            glm::vec3 up_{ 0.0f, 1.0f, 0.0f };              ///< Camera up direction.

            bool first_click_{ true };                      ///< Flag to prevent sudden jumps on first click.

			double last_mouse_x_{ 0.0};                     ///< Last mouse X position
            double last_mouse_y_{ 0.0 };                    ///< Last mouse Y position

            int width_{ 800 };                              ///< Window width.
            int height_{ 600 };                             ///< Window height.

            float speed_{ 0.1f };                          ///< Movement speed.
            float sensitivity_{ .2f };                      ///< Mouse sensitivity.

			float yaw_ = -90.0f;                            ///< Horizontal rotation angle
			float pitch_ = 0.0f;                            ///< Vertical rotation angle

            float fov_{ 45.0f };                            ///< Field of view.
            float near_plane_{ 0.1f };                      ///< Near clipping plane.
            float far_plane_{ 1000.0f };                    ///< Far clipping plane.

			Gem::Graphics::Shader* shader_{ nullptr };      ///< Pointer to the Shader object.

			Graphics::Buffer matrices_ubo_{ GL_UNIFORM_BUFFER }; ///< Buffer for matrices UBO
			const GLuint matrices_binding_point_ = 0;            ///< Binding point for the matrices UBO.
        };

	} // namespace Graphics

} // namespace Gem
