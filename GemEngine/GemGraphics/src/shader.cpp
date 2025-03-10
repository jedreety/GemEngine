#include <Gem/Graphics/shader.h>

namespace Gem {

	namespace Graphics {

		// Constructor
		Shader::Shader() {
			ID_ = GL::create_program();
			if (ID_ == 0) {
				std::cerr << "ERROR::SHADER::Failed to create shader program." << std::endl;
			}
		}

		// Destructor
		Shader::~Shader() {
			cleanup();
		}

		// Add a shader from a file
		void Shader::add_shader(GLenum shaderType, const std::string& shaderFile) {
			// Create the shader object
			GLuint shader = GL::create_shader(shaderType);
			if (shader == 0) {
				std::cerr << "ERROR::SHADER::Failed to create shader of type " << shaderType << "." << std::endl;
				throw std::runtime_error("Shader creation failed");
			}

			// Read the shader source code from the file
			std::string shaderCode = get_file_contents(shaderFile);
			const char* shaderSource = shaderCode.c_str();

			// Compile the shader
			GL::shader_source(shader, 1, &shaderSource, nullptr);
			GL::compile_shader(shader);

			// Check for compilation errors
			GLint success;
			GL::get_shader_iv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				char infoLog[1024];
				GL::get_shader_info_log(shader, sizeof(infoLog), nullptr, infoLog);
				std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << shaderType << "\n"
					<< infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
				GL::delete_shader(shader); // Avoid shader resource leak
				throw std::runtime_error("Shader compilation failed");
			}

			// Attach the shader to the program
			GL::attach_shader(ID_, shader);
			shaders_.push_back(shader); // Store for deletion after linking
		}

		// Link and validate the shader program
		void Shader::link_program() {
			// Link the shader program
			GL::link_program(ID_);

			// Check for linking errors
			GLint success;
			GL::get_program_iv(ID_, GL_LINK_STATUS, &success);
			if (!success) {
				char infoLog[1024];
				GL::get_program_info_log(ID_, sizeof(infoLog), nullptr, infoLog);
				std::cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog
					<< "\n -- --------------------------------------------------- -- " << std::endl;
				throw std::runtime_error("Program linking failed");
			}

			// Validate the shader program
			GL::validate_program(ID_);
			GL::get_program_iv(ID_, GL_VALIDATE_STATUS, &success);
			if (!success) {
				char infoLog[1024];
				GL::get_program_info_log(ID_, sizeof(infoLog), nullptr, infoLog);
				std::cerr << "ERROR::PROGRAM_VALIDATION_ERROR\n" << infoLog
					<< "\n -- --------------------------------------------------- -- " << std::endl;
				throw std::runtime_error("Program validation failed");
			}

			// Delete the shader objects now that they've been linked
			for (auto shader : shaders_) {
				GL::delete_shader(shader);
			}
			shaders_.clear();
		}

		// Activate the shader program
		void Shader::activate() const {
			GL::use_program(ID_);
		}

		// Delete the shader program
		void Shader::cleanup() {
			if (ID_ != 0) {
				GL::delete_program(ID_);
				ID_ = 0;
			}
		}

		// Set the path to the shader folder
		void Shader::set_path(const std::string& path) {
			path_ = path;
		}

		// Get the shader program ID
		[[nodiscard]] GLuint Shader::get_ID() const noexcept {
			return ID_;
		}

		// Add a uniform location to the map
		void Shader::add_uniform_location(const std::string& name) {
			GLint location = GL::get_uniform_location(ID_, name.c_str());
			if (location == -1) {
				std::cerr << "WARNING::SHADER::add_uniform_location: Uniform '" << name << "' does not exist or is not used." << std::endl;
			}
			uniform_locations_[name] = location;
		}

		// Get uniform location from the map
		GLint Shader::get_uniform_location(const std::string& name) const {
			auto it = uniform_locations_.find(name);
			if (it != uniform_locations_.end()) {
				return it->second;
			}
			else {
				std::cerr << "ERROR::SHADER::get_uniform_location: Uniform '" << name << "' not found. Did you forget to add it?" << std::endl;
				throw std::runtime_error("Uniform not found");
			}
		}

		// Set uniform methods

		// Integer uniforms
		void Shader::set_uniform(const std::string& name, GLint v0) {
			GLint location = get_uniform_location(name);
			GL::set_uniform1i(location, v0);
		}

		void Shader::set_uniform(const std::string& name, GLint v0, GLint v1) {
			GLint location = get_uniform_location(name);
			GL::set_uniform2i(location, v0, v1);
		}

		void Shader::set_uniform(const std::string& name, GLint v0, GLint v1, GLint v2) {
			GLint location = get_uniform_location(name);
			GL::set_uniform3i(location, v0, v1, v2);
		}

		void Shader::set_uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3) {
			GLint location = get_uniform_location(name);
			GL::set_uniform4i(location, v0, v1, v2, v3);
		}

		void Shader::set_uniform(const std::string& name, GLsizei count, const GLint* value) {
			GLint location = get_uniform_location(name);
			GL::set_uniform1iv(location, count, value);
		}

		// Unsigned integer uniforms
		void Shader::set_uniform(const std::string& name, GLuint v0) {
			GLint location = get_uniform_location(name);
			GL::set_uniform1ui(location, v0);
		}

		void Shader::set_uniform(const std::string& name, GLuint v0, GLuint v1) {
			GLint location = get_uniform_location(name);
			GL::set_uniform2ui(location, v0, v1);
		}

		void Shader::set_uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2) {
			GLint location = get_uniform_location(name);
			GL::set_uniform3ui(location, v0, v1, v2);
		}

		void Shader::set_uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
			GLint location = get_uniform_location(name);
			GL::set_uniform4ui(location, v0, v1, v2, v3);
		}

		void Shader::set_uniform(const std::string& name, GLsizei count, const GLuint* value) {
			GLint location = get_uniform_location(name);
			GL::set_uniform1uiv(location, count, value);
		}

		// Float uniforms
		void Shader::set_uniform(const std::string& name, GLfloat v0) {
			GLint location = get_uniform_location(name);
			GL::set_uniform1f(location, v0);
		}

		void Shader::set_uniform(const std::string& name, GLfloat v0, GLfloat v1) {
			GLint location = get_uniform_location(name);
			GL::set_uniform2f(location, v0, v1);
		}

		void Shader::set_uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) {
			GLint location = get_uniform_location(name);
			GL::set_uniform3f(location, v0, v1, v2);
		}

		void Shader::set_uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
			GLint location = get_uniform_location(name);
			GL::set_uniform4f(location, v0, v1, v2, v3);
		}

		void Shader::set_uniform(const std::string& name, GLsizei count, const GLfloat* value) {
			GLint location = get_uniform_location(name);
			GL::set_uniform1fv(location, count, value);
		}

		// Matrix uniforms
		void Shader::set_uniform_matrix(const std::string& name, const GLfloat* value, GLsizei count, GLboolean transpose, GLenum matrixType) {
			GLint location = get_uniform_location(name);
			switch (matrixType) {
			case GL_FLOAT_MAT2:
				GL::set_uniform_matrix2fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT3:
				GL::set_uniform_matrix3fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT4:
				GL::set_uniform_matrix4fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT2x3:
				GL::set_uniform_matrix2x3fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT3x2:
				GL::set_uniform_matrix3x2fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT2x4:
				GL::set_uniform_matrix2x4fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT4x2:
				GL::set_uniform_matrix4x2fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT3x4:
				GL::set_uniform_matrix3x4fv(location, count, transpose, value);
				break;
			case GL_FLOAT_MAT4x3:
				GL::set_uniform_matrix4x3fv(location, count, transpose, value);
				break;
			default:
				std::cerr << "ERROR::SHADER::set_uniform_matrix: Invalid matrix type." << std::endl;
				throw std::runtime_error("Invalid matrix type");
			}
		}

		void Shader::bind_uniform_block(const std::string& blockName, GLuint bindingPoint) {
			// Get the index of the uniform block
			GLuint blockIndex = glGetUniformBlockIndex(ID_, blockName.c_str());
			if (blockIndex == GL_INVALID_INDEX) {
				std::cerr << "WARNING::SHADER::bind_uniform_block: Uniform block '" << blockName << "' not found." << std::endl;
				return;
			}

			// Bind the uniform block to the binding point
			glUniformBlockBinding(ID_, blockIndex, bindingPoint);
		}

		// Equality operator
		bool Shader::operator==(const Shader& other) const noexcept {
			return ID_ == other.ID_;
		}

		// Inequality operator
		bool Shader::operator!=(const Shader& other) const noexcept {
			return !(*this == other);
		}

		// Read file contents
		std::string Shader::get_file_contents(const std::string& filename) const {
			std::string full_filename = path_ + filename;

			std::ifstream in(full_filename, std::ios::in | std::ios::binary);
			if (in) {
				std::ostringstream contents;
				contents << in.rdbuf();
				in.close();
				return contents.str();
			}
			std::cerr << "Could not open file: " << full_filename << "\nTry to change the path with set_path() to your local shader folder.\n";
			throw std::runtime_error("Could not open file " + full_filename);
		}

	} // namespace Graphics

} // namespace Gem
