#pragma once

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

namespace Gem {

	namespace GLAD {

		/**
		* @brief Initializes GLAD and loads OpenGL function pointers.
		*
		* This function must be called after an OpenGL context has been created
		* and made current. It loads all the necessary OpenGL function pointers
		* using GLFW's `glfwGetProcAddress`.
		*
		*/
		int init();

		/**
		 * @brief Retrieves the OpenGL version string.
		 *
		 * This function returns a string describing the version of OpenGL currently in use.
		 *
		 * @return A string containing the OpenGL version.
		 */
		std::string get_version_string();

	} // namespace GLAD

	namespace GLFW {

		/**
		* @brief Initializes the GLFW library.
		*
		* This function must be called before any other GLFW functions.
		*
		* @return True if initialization was successful, false otherwise.
		*/
		bool init();

		/**
		* @brief Terminates the GLFW library.
		*
		* Cleans up resources allocated by GLFW.
		*/
		void terminate();

		/**
		* @brief Sets a window hint.
		* 
		* @param hint The window hint to set.
		* @param value The value to set the hint to.
		*/
		void window_hint(int hint, int value);

		/**
		* @brief Sets the OpenGL context version.
		*
		* @param major Major version number.
		* @param minor Minor version number.
		*/
		void set_context_version(int major, int minor);

		/**
		* @brief Sets the OpenGL profile.
		*
		* @param profile OpenGL profile (e.g., `GLFW_OPENGL_CORE_PROFILE`).
		*/
		void set_openGL_profile(int profile);

		/**
		* @brief Enables or disables window resizability.
		*
		* @param resizable True to make the window resizable, false otherwise.
		*/
		void set_window_resizable(bool resizable);

		/**
		* @brief Creates a GLFW window with the specified parameters.
		*
		* @param width Window width in pixels.
		* @param height Window height in pixels.
		* @param title Window title.
		* @return Pointer to the created GLFWwindow.
		*
		* @throws std::runtime_error if window creation fails.
		*/
		GLFWwindow* create_window(int width, int height, const std::string& title);

		/**
		* @brief Makes the specified window's context current.
		*
		* @param window Pointer to the GLFWwindow.
		*/
		void make_context_current(GLFWwindow* window);

		/**
		* @brief Sets the swap interval for the current context (enables/disables VSync).
		*
		* @param interval Interval for buffer swapping (1 to enable VSync, 0 to disable).
		*/
		void set_swap_interval(int interval);

		/**
		 * @brief Sets the user-defined pointer of the specified window.
		 *
		 * Associates a user-defined pointer with the specified window. This can be used
		 * to store custom data related to the window.
		 *
		 * @param window The window whose user pointer to set.
		 * @param pointer The new value of the user pointer.
		 */
		void set_window_user_pointer(GLFWwindow* window, void* pointer);

		/**
		 * @brief Retrieves the user-defined pointer of the specified window.
		 *
		 * Returns the current value of the user pointer of the specified window.
		 *
		 * @param window The window whose user pointer to retrieve.
		 * @return The user pointer previously set with set_window_user_pointer.
		 */
		void* get_window_user_pointer(GLFWwindow* window);

		/**
		 * @brief Sets the close flag of the specified window.
		 *
		 * Sets the value of the close flag of the specified window, indicating whether
		 * the window should be closed.
		 *
		 * @param window The window whose close flag to set.
		 * @param value The new value of the close flag.
		 */
		void set_window_should_close(GLFWwindow* window, int value);

		/**
		 * @brief Sets the size of the window.
		 *
		 * Sets the size of the window in pixels.
		 *
		 * @param window The window to resize.
		 * @param width The new width of the window.
		 * @param height The new height of the window.
		 */
		void set_window_size(GLFWwindow* window, int width, int height);

		/**
		 * @brief Sets the title of the window.
		 *
		 * Sets the title of the window to the specified string.
		 *
		 * @param window The window to set the title of.
		 * @param title The new title of the window.
		 */
		void set_window_title(GLFWwindow* window, const char* title);

		/**
		 * @brief Checks the close flag of the specified window.
		 *
		 * Returns the value of the close flag of the specified window.
		 *
		 * @param window The window to query.
		 * @return The value of the close flag.
		 */
		int window_should_close(GLFWwindow* window);

		/**
		 * @brief Destroys the specified window and its context.
		 *
		 * Destroys the specified window and its associated context. The window pointer
		 * becomes invalid after this call.
		 *
		 * @param window The window to destroy.
		 */
		void destroy_window(GLFWwindow* window);

		/**
		 * @brief Sets the mouse button callback for the specified window.
		 *
		 * Sets the function to be called when a mouse button is pressed or released.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_mouse_button_callback(GLFWwindow* window, GLFWmousebuttonfun callback);

		/**
		 * @brief Sets the key callback for the specified window.
		 *
		 * Sets the function to be called when a key is pressed, repeated, or released.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_key_callback(GLFWwindow* window, GLFWkeyfun callback);

		/**
		 * @brief Sets the framebuffer size callback for the specified window.
		 *
		 * Sets the function to be called when the framebuffer is resized.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_framebuffer_size_callback(GLFWwindow* window, GLFWframebuffersizefun callback);

        /**
         * @brief Sets an input mode option for a specific window.
         *
         * This function sets the value of an input mode option for the specified window.
         * Input modes can control how GLFW handles keyboard input, mouse input, and more.
         *
         * @param window The window whose input mode to set.
         * @param mode The input mode whose value to set. (e.g., GLFW_CURSOR, GLFW_STICKY_KEYS)
         * @param value The new value of the specified input mode.
         */
        void set_input_mode(GLFWwindow* window, int mode, int value);

        /**
         * @brief Sets the position of the cursor relative to the content area of the window.
         *
         * This function sets the cursor position, relative to the upper-left corner of the content area
         * of the specified window.
         *
         * @param window The window whose cursor to set.
         * @param xpos The new x-coordinate of the cursor.
         * @param ypos The new y-coordinate of the cursor.
         */
        void set_cursor_pos(GLFWwindow* window, double xpos, double ypos);

        /**
         * @brief Retrieves the position of the cursor relative to the content area of the window.
         *
         * This function retrieves the current position of the cursor, relative to the upper-left corner
         * of the content area of the specified window.
         *
         * @param window The window whose cursor position to query.
         * @param xpos Pointer to a double to store the x-coordinate of the cursor.
         * @param ypos Pointer to a double to store the y-coordinate of the cursor.
         */
        void get_cursor_pos(GLFWwindow* window, double* xpos, double* ypos);

		/**
		 * @brief Sets the cursor mode for the specified window.
		 *
		 * This function sets the cursor mode for the specified window. The cursor mode determines
		 * how the cursor behaves and is displayed.
		 *
		 * @param window The window whose cursor mode to set.
		 * @param mode The new cursor mode.
		 */
		void set_cursor_mode(GLFWwindow* window, int mode);

		/**
		 * @brief Sets the cursor position callback for the specified window.
		 *
		 * This function sets the function to be called when the cursor position changes.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_cursor_pos_callback(GLFWwindow* window, GLFWcursorposfun callback);

		/**
		 * @brief Sets the scroll callback for the specified window.
		 *
		 * This function sets the function to be called when the user scrolls with a mouse wheel.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_scroll_callback(GLFWwindow* window, GLFWscrollfun callback);

		/**
		 * @brief Sets the window size callback for the specified window.
		 *
		 * This function sets the function to be called when the window is resized.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_window_size_callback(GLFWwindow* window, GLFWwindowsizefun callback);

		/**
		 * @brief Sets the window close callback for the specified window.
		 *
		 * This function sets the function to be called when the user attempts to close the window.
		 *
		 * @param window The window whose callback to set.
		 * @param callback The new callback function, or nullptr to remove the callback.
		 */
		void set_window_close_callback(GLFWwindow* window, GLFWwindowclosefun callback);

		/**
		 * @brief Swaps the front and back buffers of the specified window.
		 *
		 * This function swaps the front and back buffers of the specified window. If the window
		 * has more than one buffer, this function will also update the display.
		 *
		 * @param window The window whose buffers to swap.
		 */
		void swap_buffers(GLFWwindow* window);

		/**
		 * @brief Polls for events and processes them.
		 *
		 * This function polls for events and processes them. It should be called regularly to
		 * keep the window responsive.
		 */
		void poll_events();

	}

    namespace GL {

        /**
         * @brief Retrieves the location of a uniform variable within a shader program.
         *
         * This function returns the location of a uniform variable specified by name
         * within the given shader program. If the uniform variable does not exist,
         * or if an error occurs, the function returns -1.
         *
         * @param program The shader program object.
         * @param name The name of the uniform variable.
         * @return The location of the uniform variable, or -1 if not found.
         */
        GLint get_uniform_location(GLuint program, const std::string& name);


        /**
         * @brief Sets the value of a mat2 uniform variable in a shader program.
         *
         * This function updates the value of a 2x2 matrix uniform variable at the specified location
         * within a shader program. It can optionally transpose the matrix.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of matrices to be updated.
         * @param transpose Whether to transpose the matrices as they are loaded into the uniform variable.
         * @param value Pointer to an array of 4 float values per matrix.
         */
        void set_uniform_matrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat3 uniform variable in a shader program.
         *
         * This function updates the value of a 3x3 matrix uniform variable at the specified location
         * within a shader program. It can optionally transpose the matrix.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of matrices to be updated.
         * @param transpose Whether to transpose the matrices as they are loaded into the uniform variable.
         * @param value Pointer to an array of 9 float values per matrix.
         */
        void set_uniform_matrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat4 uniform variable in a shader program.
         *
         * This function updates the value of a 4x4 matrix uniform variable at the specified location
         * within a shader program. It can optionally transpose the matrix.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of matrices to be updated.
         * @param transpose Whether to transpose the matrices as they are loaded into the uniform variable.
         * @param value Pointer to an array of 16 float values per matrix.
         */
        void set_uniform_matrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat2x3 uniform variable in a shader program.
         *
         * Updates a 2x3 matrix uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count Number of matrices to be updated.
         * @param transpose Whether to transpose the matrices.
         * @param value Pointer to an array of 6 float values per matrix.
         */
        void set_uniform_matrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat3x2 uniform variable in a shader program.
         *
         * Updates a 3x2 matrix uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count Number of matrices to be updated.
         * @param transpose Whether to transpose the matrices.
         * @param value Pointer to an array of 6 float values per matrix.
         */
        void set_uniform_matrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat2x4 uniform variable in a shader program.
         *
         * Updates a 2x4 matrix uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count Number of matrices to be updated.
         * @param transpose Whether to transpose the matrices.
         * @param value Pointer to an array of 8 float values per matrix.
         */
        void set_uniform_matrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat4x2 uniform variable in a shader program.
         *
         * Updates a 4x2 matrix uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count Number of matrices to be updated.
         * @param transpose Whether to transpose the matrices.
         * @param value Pointer to an array of 8 float values per matrix.
         */
        void set_uniform_matrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat3x4 uniform variable in a shader program.
         *
         * Updates a 3x4 matrix uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count Number of matrices to be updated.
         * @param transpose Whether to transpose the matrices.
         * @param value Pointer to an array of 12 float values per matrix.
         */
        void set_uniform_matrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a mat4x3 uniform variable in a shader program.
         *
         * Updates a 4x3 matrix uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count Number of matrices to be updated.
         * @param transpose Whether to transpose the matrices.
         * @param value Pointer to an array of 12 float values per matrix.
         */
        void set_uniform_matrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

        /**
         * @brief Sets the value of a 1-integer uniform variable in a shader program.
         *
         * Updates a single integer uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 The integer value to set.
         */
        void set_uniform1i(GLint location, GLint v0);

        /**
         * @brief Sets the value of a 2-integer uniform variable in a shader program.
         *
         * Updates a vec2i uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First integer value.
         * @param v1 Second integer value.
         */
        void set_uniform2i(GLint location, GLint v0, GLint v1);

        /**
         * @brief Sets the value of a 3-integer uniform variable in a shader program.
         *
         * Updates a vec3i uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First integer value.
         * @param v1 Second integer value.
         * @param v2 Third integer value.
         */
        void set_uniform3i(GLint location, GLint v0, GLint v1, GLint v2);

        /**
         * @brief Sets the value of a 4-integer uniform variable in a shader program.
         *
         * Updates a vec4i uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First integer value.
         * @param v1 Second integer value.
         * @param v2 Third integer value.
         * @param v3 Fourth integer value.
         */
        void set_uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

        /**
         * @brief Sets the value of a 1-integer vector uniform variable in a shader program.
         *
         * Updates a single integer uniform variable or an array of integers at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of elements to be updated.
         * @param value Pointer to the integer values.
         */
        void set_uniform1iv(GLint location, GLsizei count, const GLint* value);

        /**
         * @brief Sets the value of a 2-integer vector uniform variable in a shader program.
         *
         * Updates a vec2i uniform variable or an array of vec2i at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of vec2i elements to be updated.
         * @param value Pointer to the integer values.
         */
        void set_uniform2iv(GLint location, GLsizei count, const GLint* value);

        /**
         * @brief Sets the value of a 3-integer vector uniform variable in a shader program.
         *
         * Updates a vec3i uniform variable or an array of vec3i at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of vec3i elements to be updated.
         * @param value Pointer to the integer values.
         */
        void set_uniform3iv(GLint location, GLsizei count, const GLint* value);

        /**
         * @brief Sets the value of a 4-integer vector uniform variable in a shader program.
         *
         * Updates a vec4i uniform variable or an array of vec4i at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of vec4i elements to be updated.
         * @param value Pointer to the integer values.
         */
        void set_uniform4iv(GLint location, GLsizei count, const GLint* value);

        /**
         * @brief Sets the value of a 1-float uniform variable in a shader program.
         *
         * Updates a single float uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 The float value to set.
         */
        void set_uniform1f(GLint location, GLfloat v0);

        /**
         * @brief Sets the value of a 2-float uniform variable in a shader program.
         *
         * Updates a vec2 uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First float value.
         * @param v1 Second float value.
         */
        void set_uniform2f(GLint location, GLfloat v0, GLfloat v1);

        /**
         * @brief Sets the value of a 3-float uniform variable in a shader program.
         *
         * Updates a vec3 uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First float value.
         * @param v1 Second float value.
         * @param v2 Third float value.
         */
        void set_uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);

        /**
         * @brief Sets the value of a 4-float uniform variable in a shader program.
         *
         * Updates a vec4 uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First float value.
         * @param v1 Second float value.
         * @param v2 Third float value.
         * @param v3 Fourth float value.
         */
        void set_uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

        /**
         * @brief Sets the value of a 1-float vector uniform variable in a shader program.
         *
         * Updates a single float uniform variable or an array of floats at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of elements to be updated.
         * @param value Pointer to the float values.
         */
        void set_uniform1fv(GLint location, GLsizei count, const GLfloat* value);

        /**
         * @brief Sets the value of a 2-float vector uniform variable in a shader program.
         *
         * Updates a vec2 uniform variable or an array of vec2 at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of vec2 elements to be updated.
         * @param value Pointer to the float values.
         */
        void set_uniform2fv(GLint location, GLsizei count, const GLfloat* value);

        /**
         * @brief Sets the value of a 3-float vector uniform variable in a shader program.
         *
         * Updates a vec3 uniform variable or an array of vec3 at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of vec3 elements to be updated.
         * @param value Pointer to the float values.
         */
        void set_uniform3fv(GLint location, GLsizei count, const GLfloat* value);

        /**
         * @brief Sets the value of a 4-float vector uniform variable in a shader program.
         *
         * Updates a vec4 uniform variable or an array of vec4 at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of vec4 elements to be updated.
         * @param value Pointer to the float values.
         */
        void set_uniform4fv(GLint location, GLsizei count, const GLfloat* value);

        /**
         * @brief Sets the value of a 1-unsigned integer uniform variable in a shader program.
         *
         * Updates a single unsigned integer uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 The unsigned integer value to set.
         */
        void set_uniform1ui(GLint location, GLuint v0);

        /**
         * @brief Sets the value of a 2-unsigned integer uniform variable in a shader program.
         *
         * Updates a uvec2 uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First unsigned integer value.
         * @param v1 Second unsigned integer value.
         */
        void set_uniform2ui(GLint location, GLuint v0, GLuint v1);

        /**
         * @brief Sets the value of a 3-unsigned integer uniform variable in a shader program.
         *
         * Updates a uvec3 uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First unsigned integer value.
         * @param v1 Second unsigned integer value.
         * @param v2 Third unsigned integer value.
         */
        void set_uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2);

        /**
         * @brief Sets the value of a 4-unsigned integer uniform variable in a shader program.
         *
         * Updates a uvec4 uniform variable at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param v0 First unsigned integer value.
         * @param v1 Second unsigned integer value.
         * @param v2 Third unsigned integer value.
         * @param v3 Fourth unsigned integer value.
         */
        void set_uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);

        /**
         * @brief Sets the value of a 1-unsigned integer vector uniform variable in a shader program.
         *
         * Updates a single unsigned integer uniform variable or an array of unsigned integers at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of elements to be updated.
         * @param value Pointer to the unsigned integer values.
         */
        void set_uniform1uiv(GLint location, GLsizei count, const GLuint* value);

        /**
         * @brief Sets the value of a 2-unsigned integer vector uniform variable in a shader program.
         *
         * Updates a uvec2 uniform variable or an array of uvec2 at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of uvec2 elements to be updated.
         * @param value Pointer to the unsigned integer values.
         */
        void set_uniform2uiv(GLint location, GLsizei count, const GLuint* value);

        /**
         * @brief Sets the value of a 3-unsigned integer vector uniform variable in a shader program.
         *
         * Updates a uvec3 uniform variable or an array of uvec3 at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of uvec3 elements to be updated.
         * @param value Pointer to the unsigned integer values.
         */
        void set_uniform3uiv(GLint location, GLsizei count, const GLuint* value);

        /**
         * @brief Sets the value of a 4-unsigned integer vector uniform variable in a shader program.
         *
         * Updates a uvec4 uniform variable or an array of uvec4 at the specified location.
         *
         * @param location The location of the uniform variable to be updated.
         * @param count The number of uvec4 elements to be updated.
         * @param value Pointer to the unsigned integer values.
         */
        void set_uniform4uiv(GLint location, GLsizei count, const GLuint* value);

        /**
         * @brief Sets texture parameters for the specified target.
         *
         * Specifies the value of a texture parameter for the specified target and parameter name.
         *
         * @param target Specifies the target texture (e.g., GL_TEXTURE_2D, GL_TEXTURE_3D).
         * @param pname Specifies the symbolic name of a single-valued texture parameter (e.g., GL_TEXTURE_MIN_FILTER).
         * @param param Specifies the value of pname.
         */
        void tex_parameteri(GLenum target, GLenum pname, GLint param);

        /**
         * @brief Deletes named textures.
         *
         * Deletes n textures named by the elements of the array textures.
         *
         * @param n Specifies the number of textures to be deleted.
         * @param textures Specifies an array of textures to be deleted.
         */
        void delete_textures(GLsizei n, const GLuint* textures);

        /**
         * @brief Specifies storage for a three-dimensional texture.
         *
         * Specifies storage for all levels of a three-dimensional or two-dimensional array texture.
         *
         * @param target Specifies the target of the operation (e.g., GL_TEXTURE_3D, GL_TEXTURE_2D_ARRAY).
         * @param levels Specifies the number of texture levels.
         * @param internalformat Specifies the sized internal format to be used to store texture image data.
         * @param width Specifies the width of the texture, in texels.
         * @param height Specifies the height of the texture, in texels.
         * @param depth Specifies the depth of the texture, in texels.
         */
        void tex_storage_3d(GLenum target, GLsizei levels, GLenum internalformat,
            GLsizei width, GLsizei height, GLsizei depth);

        /**
         * @brief Generates texture names.
         *
         * Generates n texture names and stores them in textures.
         *
         * @param n Specifies the number of texture names to be generated.
         * @param textures Specifies an array in which the generated texture names are stored.
         */
        void gen_textures(GLsizei n, GLuint* textures);

        /**
         * @brief Selects active texture unit.
         *
         * Selects which texture unit subsequent texture state calls will affect.
         *
         * @param texture Specifies which texture unit to make active. The number of texture units is implementation dependent, starting from GL_TEXTURE0.
         */
        void active_texture(GLenum texture);

        /**
         * @brief Binds a named texture to a texturing target.
         *
         * Binds the texture named texture to the specified target.
         *
         * @param target Specifies the target to which the texture is bound (e.g., GL_TEXTURE_2D, GL_TEXTURE_3D).
         * @param texture Specifies the name of a texture.
         */
        void bind_texture(GLenum target, GLuint texture);

        /**
         * @brief Generates mipmaps for the specified texture target.
         *
         * Generates mipmaps for the specified texture target bound to the active texture unit.
         *
         * @param target Specifies the target to which the texture is bound (e.g., GL_TEXTURE_2D, GL_TEXTURE_3D).
         */
        void generate_mipmap(GLenum target);

        /**
         * @brief Specifies a three-dimensional texture image.
         *
         * @param target Specifies the target texture (e.g., GL_TEXTURE_3D).
         * @param level Specifies the level-of-detail number.
         * @param internalformat Specifies the number of color components in the texture.
         * @param width Specifies the width of the texture image.
         * @param height Specifies the height of the texture image.
         * @param depth Specifies the depth of the texture image.
         * @param border Specifies the width of the border. Must be 0.
         * @param format Specifies the format of the pixel data (e.g., GL_RGBA).
         * @param type Specifies the data type of the pixel data (e.g., GL_UNSIGNED_BYTE).
         * @param pixels Specifies a pointer to the image data in memory.
         */
        void tex_image_3d(GLenum target, GLint level, GLint internalformat,
            GLsizei width, GLsizei height, GLsizei depth, GLint border,
            GLenum format, GLenum type, const void* pixels);

        /**
         * @brief Specifies a three-dimensional texture subimage.
         *
         * Specifies a three-dimensional texture subimage, replacing a portion of an existing three-dimensional texture image.
         *
         * @param target Specifies the target texture (e.g., GL_TEXTURE_3D).
         * @param level Specifies the level-of-detail number.
         * @param xoffset Specifies the x offset of the texture subregion.
         * @param yoffset Specifies the y offset of the texture subregion.
         * @param zoffset Specifies the z offset of the texture subregion.
         * @param width Specifies the width of the texture subregion.
         * @param height Specifies the height of the texture subregion.
         * @param depth Specifies the depth of the texture subregion.
         * @param format Specifies the format of the pixel data (e.g., GL_RGBA).
         * @param type Specifies the data type of the pixel data (e.g., GL_UNSIGNED_BYTE).
         * @param pixels Specifies a pointer to the image data in memory.
         */
        void tex_sub_image_3d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
            GLsizei width, GLsizei height, GLsizei depth,
            GLenum format, GLenum type, const void* pixels);

        /**
         * @brief Specifies a two-dimensional texture image.
         *
         * Specifies a two-dimensional texture image.
         *
         * @param target Specifies the target texture (e.g., GL_TEXTURE_2D).
         * @param level Specifies the level-of-detail number.
         * @param internalformat Specifies the number of color components in the texture.
         * @param width Specifies the width of the texture image.
         * @param height Specifies the height of the texture image.
         * @param border Specifies the width of the border. Must be 0.
         * @param format Specifies the format of the pixel data (e.g., GL_RGBA).
         * @param type Specifies the data type of the pixel data (e.g., GL_UNSIGNED_BYTE).
         * @param pixels Specifies a pointer to the image data in memory.
         */
        void tex_image_2d(GLenum target, GLint level, GLint internalformat,
            GLsizei width, GLsizei height, GLint border,
            GLenum format, GLenum type, const void* pixels);

        /**
         * @brief Specifies a two-dimensional texture subimage.
         *
         * Specifies a two-dimensional texture subimage, replacing a portion of an existing two-dimensional texture image.
         *
         * @param target Specifies the target texture (e.g., GL_TEXTURE_2D).
         * @param level Specifies the level-of-detail number.
         * @param xoffset Specifies the x offset of the texture subregion.
         * @param yoffset Specifies the y offset of the texture subregion.
         * @param width Specifies the width of the texture subregion.
         * @param height Specifies the height of the texture subregion.
         * @param format Specifies the format of the pixel data (e.g., GL_RGBA).
         * @param type Specifies the data type of the pixel data (e.g., GL_UNSIGNED_BYTE).
         * @param pixels Specifies a pointer to the image data in memory.
         */
        void tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset,
            GLsizei width, GLsizei height,
            GLenum format, GLenum type, const void* pixels);

        /**
         * @brief Specifies storage for a two-dimensional texture.
         *
         * Specifies storage for all levels of a two-dimensional texture.
         *
         * @param target Specifies the target of the operation (e.g., GL_TEXTURE_2D).
         * @param levels Specifies the number of texture levels.
         * @param internalformat Specifies the sized internal format to be used to store texture image data.
         * @param width Specifies the width of the texture, in pixels.
         * @param height Specifies the height of the texture, in pixels.
         */
        void tex_storage_2d(GLenum target, GLsizei levels, GLenum internalformat,
            GLsizei width, GLsizei height);
        /**
         * @brief Specifies a one-dimensional texture image.
         *
         * @param target Specifies the target texture (e.g., GL_TEXTURE_1D).
         * @param level Specifies the level-of-detail number.
         * @param internalformat Specifies the number of color components in the texture.
         * @param width Specifies the width of the texture image.
         * @param border Specifies the width of the border. Must be 0.
         * @param format Specifies the format of the pixel data (e.g., GL_RGBA).
         * @param type Specifies the data type of the pixel data (e.g., GL_UNSIGNED_BYTE).
         * @param pixels Specifies a pointer to the image data in memory.
         */
        void tex_image_1d(GLenum target, GLint level, GLint internalformat,
            GLsizei width, GLint border,
            GLenum format, GLenum type, const void* pixels);

        /**
         * @brief Generates buffer object names.
         *
         * Generates n buffer object names and stores them in buffers.
         *
         * @param n Specifies the number of buffer object names to be generated.
         * @param buffers Specifies an array in which the generated buffer object names are stored.
         */
        void gen_buffers(GLsizei n, GLuint* buffers);

        /**
         * @brief Binds a named buffer object.
         *
         * Binds a buffer object to the specified buffer binding point (target).
         *
         * @param target Specifies the target to which the buffer object is bound (e.g., GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER).
         * @param buffer Specifies the name of a buffer object.
         */
        void bind_buffer(GLenum target, GLuint buffer);

        /**
         * @brief Creates and initializes a buffer object's data store.
         *
         * Creates a new data store for the buffer object currently bound to target.
         *
         * @param target Specifies the target buffer object (e.g., GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER).
         * @param size Specifies the size in bytes of the buffer object's new data store.
         * @param data Specifies a pointer to data that will be copied into the data store for initialization, or nullptr if no data is to be copied.
         * @param usage Specifies the expected usage pattern of the data store (e.g., GL_STATIC_DRAW, GL_DYNAMIC_DRAW).
         */
        void buffer_data(GLenum target, GLsizeiptr size, const void* data, GLenum usage);

        /**
         * @brief Deletes named buffer objects.
         *
         * Deletes n buffer objects named by the elements of the array buffers.
         *
         * @param n Specifies the number of buffer objects to be deleted.
         * @param buffers Specifies an array of buffer objects to be deleted.
         */
        void delete_buffers(GLsizei n, const GLuint* buffers);

        /**
         * @brief Generates vertex array object names.
         *
         * Generates n vertex array object names and stores them in arrays.
         *
         * @param n Specifies the number of vertex array object names to be generated.
         * @param arrays Specifies an array in which the generated vertex array object names are stored.
         */
        void gen_vertex_arrays(GLsizei n, GLuint* arrays);

        /**
         * @brief Binds a vertex array object.
         *
         * Binds the vertex array object with name array.
         *
         * @param array Specifies the name of the vertex array to bind.
         */
        void bind_vertex_array(GLuint array);

        /**
         * @brief Defines an array of generic vertex attribute data.
         *
         * Specifies the location and data format of the array of generic vertex attributes at index to use when rendering.
         *
         * @param index Specifies the index of the generic vertex attribute to be modified.
         * @param size Specifies the number of components per generic vertex attribute.
         * @param type Specifies the data type of each component in the array.
         * @param normalized Specifies whether fixed-point data values should be normalized.
         * @param stride Specifies the byte offset between consecutive generic vertex attributes.
         * @param pointer Specifies a pointer to the first component of the first generic vertex attribute in the array.
         */
        void vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

        /**
         * @brief Enables a generic vertex attribute array.
         *
         * Enables the generic vertex attribute array specified by index.
         *
         * @param index Specifies the index of the generic vertex attribute to be enabled.
         */
        void enable_vertex_attrib_array(GLuint index);

        /**
         * @brief Deletes vertex array objects.
         *
         * Deletes n vertex array objects named by the elements of the array arrays.
         *
         * @param n Specifies the number of vertex array objects to be deleted.
         * @param arrays Specifies an array of vertex array objects to be deleted.
         */
        void delete_vertex_arrays(GLsizei n, const GLuint* arrays);

        /**
         * @brief Creates a new program object.
         *
         * Creates an empty program object and returns its handle.
         *
         * @return The handle of the created program object.
         */
        GLuint create_program();

        /**
         * @brief Creates a shader object.
         *
         * Creates a shader object of the specified type and returns its handle.
         *
         * @param shaderType Specifies the type of shader to be created (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
         * @return The handle of the created shader object.
         */
        GLuint create_shader(GLenum shaderType);

        /**
         * @brief Replaces the source code in a shader object.
         *
         * Sets the source code in the shader object to the specified string.
         *
         * @param shader Specifies the shader object whose source code is to be replaced.
         * @param count Specifies the number of elements in the string and length arrays.
         * @param string Specifies an array of pointers to strings containing the source code to be loaded into the shader.
         * @param length Specifies an array of string lengths, or nullptr if the strings are null-terminated.
         */
        void shader_source(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);

        /**
         * @brief Compiles a shader object.
         *
         * Compiles the source code strings that have been stored in the shader object.
         *
         * @param shader Specifies the shader object to be compiled.
         */
        void compile_shader(GLuint shader);

        /**
         * @brief Retrieves a shader parameter.
         *
         * Returns a parameter from a shader object.
         *
         * @param shader Specifies the shader object to be queried.
         * @param pname Specifies the object parameter (e.g., GL_COMPILE_STATUS).
         * @param params Returns the requested parameter.
         */
        void get_shader_iv(GLuint shader, GLenum pname, GLint* params);

        /**
         * @brief Retrieves the information log for a shader object.
         *
         * Returns the information log for the specified shader object.
         *
         * @param shader Specifies the shader object whose information log is to be retrieved.
         * @param maxLength Specifies the size of the character buffer for the information log.
         * @param length Returns the length of the string returned in infoLog (excluding the null terminator).
         * @param infoLog Specifies an array of characters that is used to return the information log.
         */
        void get_shader_info_log(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog);

        /**
         * @brief Deletes a shader object.
         *
         * Deletes the shader object specified by shader.
         *
         * @param shader Specifies the shader object to be deleted.
         */
        void delete_shader(GLuint shader);

        /**
         * @brief Attaches a shader object to a program object.
         *
         * Attaches the shader object to the program object.
         *
         * @param program Specifies the program object to which a shader object will be attached.
         * @param shader Specifies the shader object that is to be attached.
         */
        void attach_shader(GLuint program, GLuint shader);

        /**
         * @brief Links a program object.
         *
         * Links the program object, which contains all the shader objects attached to it.
         *
         * @param program Specifies the program object to be linked.
         */
        void link_program(GLuint program);

        /**
         * @brief Retrieves a program parameter.
         *
         * Returns a parameter from a program object.
         *
         * @param program Specifies the program object to be queried.
         * @param pname Specifies the object parameter (e.g., GL_LINK_STATUS).
         * @param params Returns the requested parameter.
         */
        void get_program_iv(GLuint program, GLenum pname, GLint* params);

        /**
         * @brief Retrieves the information log for a program object.
         *
         * Returns the information log for the specified program object.
         *
         * @param program Specifies the program object whose information log is to be retrieved.
         * @param maxLength Specifies the size of the character buffer for the information log.
         * @param length Returns the length of the string returned in infoLog (excluding the null terminator).
         * @param infoLog Specifies an array of characters that is used to return the information log.
         */
        void get_program_info_log(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog);

        /**
         * @brief Validates a program object.
         *
         * Validates the program object to determine whether it is usable.
         *
         * @param program Specifies the program object to be validated.
         */
        void validate_program(GLuint program);

        /**
         * @brief Installs a program object as part of the current rendering state.
         *
         * Installs the program object specified by program as part of the current rendering state.
         *
         * @param program Specifies the handle of the program object to use.
         */
        void use_program(GLuint program);

        /**
         * @brief Deletes a program object.
         *
         * Deletes the program object specified by program.
         *
         * @param program Specifies the program object to be deleted.
         */
        void delete_program(GLuint program);

        /**
         * @brief Specifies the clear values for the color buffers.
         *
         * Sets the values used by glClear to clear the color buffers. Each value is
         * clamped between 0 and 1.
         *
         * @param red The red value used when the color buffers are cleared.
         * @param green The green value used when the color buffers are cleared.
         * @param blue The blue value used when the color buffers are cleared.
         * @param alpha The alpha value used when the color buffers are cleared.
         */
        void clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

        /**
         * @brief Sets the viewport.
         *
         * Defines the affine transformation of x and y from normalized device coordinates to window coordinates.
         *
         * @param x Specifies the lower left corner of the viewport rectangle, in pixels.
         * @param y Specifies the lower left corner of the viewport rectangle, in pixels.
         * @param width Specifies the width of the viewport.
         * @param height Specifies the height of the viewport.
         */
        void viewport(GLint x, GLint y, GLsizei width, GLsizei height);

        /**
         * @brief Clears buffers to preset values.
         *
         * This function clears the specified buffer(s) to their preset values. The preset values can be set using functions like glClearColor.
         *
         * @param mask Bitwise OR of masks that indicate the buffers to be cleared (e.g., GL_COLOR_BUFFER_BIT).
         */
        void clear(GLbitfield mask);

        /**
         * @brief Renders primitives from array data.
         *
         * This function renders primitives from array data, taking indices to specify the order.
         *
         * @param mode Specifies what kind of primitives to render (e.g., GL_TRIANGLES).
         * @param count Specifies the number of elements to be rendered.
         * @param type Specifies the type of the values in indices (e.g., GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT).
         * @param indices Specifies a pointer to the location where the indices are stored.
         */
        void draw_elements(GLenum mode, GLsizei count, GLenum type, const void* indices);

        /**
         * @brief Enables or disables server-side GL capabilities.
         *
         * This function enables a server-side OpenGL capability.
         *
         * @param cap Specifies a symbolic constant indicating a capability (e.g., GL_DEPTH_TEST).
         */
        void enable(GLenum cap);

        /**
         * @brief Disables server-side GL capabilities.
         *
         * This function disables a server-side OpenGL capability.
         *
         * @param cap Specifies a symbolic constant indicating a capability (e.g., GL_BLEND).
         */
        void disable(GLenum cap);

        /**
         * @brief Retrieves error information.
         *
         * This function returns the value of the error flag, which indicates whether an error has occurred.
         *
         * @return Returns the value of the error flag (e.g., GL_NO_ERROR).
         */
        GLenum get_error();

    } // namespace GL


} // Gem