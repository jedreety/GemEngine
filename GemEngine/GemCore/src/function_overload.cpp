#include <function_overload.h>
#include <stdexcept>

namespace Gem {

	namespace GLAD {

		//|========================================================= Init =========================================================================================

		int init() {
			return gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		}

		//|========================================================= Version =========================================================================================

		std::string get_version_string() {
			const GLubyte* version = glGetString(GL_VERSION);
			if (version) {
				return reinterpret_cast<const char*>(version);
			}
			else {
				return "ERROR::GLAD::get_version_string: Failed to retrieve OpenGL version string.";
			}
		}


	} // namespace GLAD

	namespace GLFW {

		bool init() {
			return glfwInit();
		}

		void terminate() {
			glfwTerminate();
		}
		//|========================================================= Context - Profile =========================================================================================

		void window_hint(int hint, int value) {
			glfwWindowHint(hint, value);
		}

		void set_context_version(int major, int minor) {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		}

		void set_openGL_profile(int profile) {
			glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
		}

		//|========================================================= Window =========================================================================================

		void set_window_resizable(bool resizable) {
			glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);
		}

		GLFWwindow* create_window(int width, int height, const std::string& title) {
			return glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		}

		void make_context_current(GLFWwindow* window) {
			glfwMakeContextCurrent(window);
		}

		void set_swap_interval(int interval) {
			glfwSwapInterval(interval);
		}

		void set_window_user_pointer(GLFWwindow* window, void* pointer) {
			glfwSetWindowUserPointer(window, pointer);
		}

		void* get_window_user_pointer(GLFWwindow* window) {
			return glfwGetWindowUserPointer(window);
		}

		void set_window_should_close(GLFWwindow* window, int value) {
			glfwSetWindowShouldClose(window, value);
		}

		void set_window_size(GLFWwindow* window, int width, int height) {
			glfwSetWindowSize(window, width, height);
		}

		void set_window_title(GLFWwindow* window, const char* title) {
			glfwSetWindowTitle(window, title);
		}

		int window_should_close(GLFWwindow* window) {
			return glfwWindowShouldClose(window);
		}

		void destroy_window(GLFWwindow* window) {
			glfwDestroyWindow(window);
		}

		void set_mouse_button_callback(GLFWwindow* window, GLFWmousebuttonfun callback) {
			glfwSetMouseButtonCallback(window, callback);
		}

		void set_key_callback(GLFWwindow* window, GLFWkeyfun callback) {
			glfwSetKeyCallback(window, callback);
		}

		void set_framebuffer_size_callback(GLFWwindow* window, GLFWframebuffersizefun callback) {
			glfwSetFramebufferSizeCallback(window, callback);
		}

		void set_input_mode(GLFWwindow* window, int mode, int value) {
			glfwSetInputMode(window, mode, value);
		}

		void set_cursor_pos(GLFWwindow* window, double xpos, double ypos) {
			glfwSetCursorPos(window, xpos, ypos);
		}

		void get_cursor_pos(GLFWwindow* window, double* xpos, double* ypos) {
			glfwGetCursorPos(window, xpos, ypos);
		}

		void set_cursor_mode(GLFWwindow* window, int mode) {
			glfwSetInputMode(window, GLFW_CURSOR, mode);
		}

		void set_cursor_pos_callback(GLFWwindow* window, GLFWcursorposfun callback) {
			glfwSetCursorPosCallback(window, callback);
		}

		void set_scroll_callback(GLFWwindow* window, GLFWscrollfun callback) {
			glfwSetScrollCallback(window, callback);
		}

		void set_window_size_callback(GLFWwindow* window, GLFWwindowsizefun callback) {
			glfwSetWindowSizeCallback(window, callback);
		}

		void set_window_close_callback(GLFWwindow* window, GLFWwindowclosefun callback) {
			glfwSetWindowCloseCallback(window, callback);
		}

		void swap_buffers(GLFWwindow* window) {
			glfwSwapBuffers(window);
		}

		void poll_events() {
			glfwPollEvents();
		}

	} // namespace GLFW

	namespace GL {

		//|========================================================= Uniforms =============================================================================================

		GLint get_uniform_location(GLuint program, const std::string& name) {
			return glGetUniformLocation(program, name.c_str());
		}

		void set_uniform_matrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix2fv(location, count, transpose, value);
		}

		void set_uniform_matrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix3fv(location, count, transpose, value);
		}

		void set_uniform_matrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix4fv(location, count, transpose, value);
		}

		void set_uniform_matrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix2x3fv(location, count, transpose, value);
		}

		void set_uniform_matrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix3x2fv(location, count, transpose, value);
		}

		void set_uniform_matrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix2x4fv(location, count, transpose, value);
		}

		void set_uniform_matrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix4x2fv(location, count, transpose, value);
		}

		void set_uniform_matrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix3x4fv(location, count, transpose, value);
		}

		void set_uniform_matrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
			glUniformMatrix4x3fv(location, count, transpose, value);
		}

		void set_uniform1i(GLint location, GLint v0) {
			glUniform1i(location, v0);
		}

		void set_uniform2i(GLint location, GLint v0, GLint v1) {
			glUniform2i(location, v0, v1);
		}

		void set_uniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
			glUniform3i(location, v0, v1, v2);
		}

		void set_uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
			glUniform4i(location, v0, v1, v2, v3);
		}

		void set_uniform1iv(GLint location, GLsizei count, const GLint* value) {
			glUniform1iv(location, count, value);
		}

		void set_uniform2iv(GLint location, GLsizei count, const GLint* value) {
			glUniform2iv(location, count, value);
		}

		void set_uniform3iv(GLint location, GLsizei count, const GLint* value) {
			glUniform3iv(location, count, value);
		}

		void set_uniform4iv(GLint location, GLsizei count, const GLint* value) {
			glUniform4iv(location, count, value);
		}

		void set_uniform1f(GLint location, GLfloat v0) {
			glUniform1f(location, v0);
		}

		void set_uniform2f(GLint location, GLfloat v0, GLfloat v1) {
			glUniform2f(location, v0, v1);
		}

		void set_uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
			glUniform3f(location, v0, v1, v2);
		}

		void set_uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
			glUniform4f(location, v0, v1, v2, v3);
		}

		void set_uniform1fv(GLint location, GLsizei count, const GLfloat* value) {
			glUniform1fv(location, count, value);
		}

		void set_uniform2fv(GLint location, GLsizei count, const GLfloat* value) {
			glUniform2fv(location, count, value);
		}

		void set_uniform3fv(GLint location, GLsizei count, const GLfloat* value) {
			glUniform3fv(location, count, value);
		}

		void set_uniform4fv(GLint location, GLsizei count, const GLfloat* value) {
			glUniform4fv(location, count, value);
		}

		void set_uniform1ui(GLint location, GLuint v0) {
			glUniform1ui(location, v0);
		}

		void set_uniform2ui(GLint location, GLuint v0, GLuint v1) {
			glUniform2ui(location, v0, v1);
		}

		void set_uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
			glUniform3ui(location, v0, v1, v2);
		}

		void set_uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
			glUniform4ui(location, v0, v1, v2, v3);
		}

		void set_uniform1uiv(GLint location, GLsizei count, const GLuint* value) {
			glUniform1uiv(location, count, value);
		}

		void set_uniform2uiv(GLint location, GLsizei count, const GLuint* value) {
			glUniform2uiv(location, count, value);
		}

		void set_uniform3uiv(GLint location, GLsizei count, const GLuint* value) {
			glUniform3uiv(location, count, value);
		}

		void set_uniform4uiv(GLint location, GLsizei count, const GLuint* value) {
			glUniform4uiv(location, count, value);
		}

		//|========================================================= Textures ==============================================================================================

		void tex_parameteri(GLenum target, GLenum pname, GLint param) {
			glTexParameteri(target, pname, param);
		}

		void delete_textures(GLsizei n, const GLuint* textures) {
			glDeleteTextures(n, textures);
		}

		void tex_storage_3d(GLenum target, GLsizei levels, GLenum internalformat,
			GLsizei width, GLsizei height, GLsizei depth) {
			glTexStorage3D(target, levels, internalformat, width, height, depth);
		}

		void gen_textures(GLsizei n, GLuint* textures) {
			glGenTextures(n, textures);
		}

		void active_texture(GLenum texture) {
			glActiveTexture(texture);
		}

		void bind_texture(GLenum target, GLuint texture) {
			glBindTexture(target, texture);
		}

		void generate_mipmap(GLenum target) {
			glGenerateMipmap(target);
		}

		void tex_image_3d(GLenum target, GLint level, GLint internalformat,
			GLsizei width, GLsizei height, GLsizei depth, GLint border,
			GLenum format, GLenum type, const void* pixels) {
			glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
		}

		void tex_sub_image_3d(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,
			GLsizei width, GLsizei height, GLsizei depth,
			GLenum format, GLenum type, const void* pixels) {
			glTexSubImage3D(target, level, xoffset, yoffset, zoffset,
				width, height, depth, format, type, pixels);
		}

		void tex_image_2d(GLenum target, GLint level, GLint internalformat,
			GLsizei width, GLsizei height, GLint border,
			GLenum format, GLenum type, const void* pixels) {
			glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		}

		void tex_sub_image_2d(GLenum target, GLint level, GLint xoffset, GLint yoffset,
			GLsizei width, GLsizei height,
			GLenum format, GLenum type, const void* pixels) {
			glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
		}

		void tex_storage_2d(GLenum target, GLsizei levels, GLenum internalformat,
			GLsizei width, GLsizei height) {
			glTexStorage2D(target, levels, internalformat, width, height);
		}

		void tex_image_1d(GLenum target, GLint level, GLint internalformat,
			GLsizei width, GLint border,
			GLenum format, GLenum type, const void* pixels) {
			glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
		}

		//|========================================================= Buffers ===============================================================================================

		void gen_buffers(GLsizei n, GLuint* buffers) {
			glGenBuffers(n, buffers);
		}

		void bind_buffer(GLenum target, GLuint buffer) {
			glBindBuffer(target, buffer);
		}

		void buffer_data(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
			glBufferData(target, size, data, usage);
		}

		void delete_buffers(GLsizei n, const GLuint* buffers) {
			glDeleteBuffers(n, buffers);
		}

		//|========================================================= Vertex Arrays =========================================================================================

		void gen_vertex_arrays(GLsizei n, GLuint* arrays) {
			glGenVertexArrays(n, arrays);
		}

		void bind_vertex_array(GLuint array) {
			glBindVertexArray(array);
		}

		void vertex_attrib_pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
		}

		void enable_vertex_attrib_array(GLuint index) {
			glEnableVertexAttribArray(index);
		}

		void delete_vertex_arrays(GLsizei n, const GLuint* arrays) {
			glDeleteVertexArrays(n, arrays);
		}

		//|========================================================= Shader =========================================================================================

		GLuint create_shader(GLenum shaderType) {
			return glCreateShader(shaderType);
		}

		void shader_source(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
			glShaderSource(shader, count, string, length);
		}

		void compile_shader(GLuint shader) {
			glCompileShader(shader);
		}

		void get_shader_iv(GLuint shader, GLenum pname, GLint* params) {
			glGetShaderiv(shader, pname, params);
		}

		void get_shader_info_log(GLuint shader, GLsizei maxLength, GLsizei* length, GLchar* infoLog) {
			glGetShaderInfoLog(shader, maxLength, length, infoLog);
		}

		void delete_shader(GLuint shader) {
			glDeleteShader(shader);
		}

		void attach_shader(GLuint program, GLuint shader) {
			glAttachShader(program, shader);
		}

		//|========================================================= Program =========================================================================================

		GLuint create_program() {
			return glCreateProgram();
		}

		void link_program(GLuint program) {
			glLinkProgram(program);
		}

		void get_program_iv(GLuint program, GLenum pname, GLint* params) {
			glGetProgramiv(program, pname, params);
		}

		void get_program_info_log(GLuint program, GLsizei maxLength, GLsizei* length, GLchar* infoLog) {
			glGetProgramInfoLog(program, maxLength, length, infoLog);
		}

		void validate_program(GLuint program) {
			glValidateProgram(program);
		}

		void use_program(GLuint program) {
			glUseProgram(program);
		}

		void delete_program(GLuint program) {
			glDeleteProgram(program);
		}

		//|========================================================= Frame buffers =========================================================================================

		void clear_color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
			glClearColor(red, green, blue, alpha);
		}

		void viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
			glViewport(x, y, width, height);
		}

		void clear(GLbitfield mask) {
			glClear(mask);
		}

		void draw_elements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
			glDrawElements(mode, count, type, indices);
		}

		//|========================================================= Server Side =========================================================================================

		void enable(GLenum cap) {
			glEnable(cap);
		}

		void disable(GLenum cap) {
			glDisable(cap);
		}

		//|========================================================= Error =========================================================================================

		GLenum get_error() {
			return glGetError();
		}

	} // namespace GL

} // Gem