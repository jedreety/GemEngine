#pragma once

#include <../../GemCore/include-protected/function_overload.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace Gem {

    namespace Graphics {

        /**
         * @brief Shader class for managing OpenGL shader programs.
         *
         * The Shader class encapsulates the creation, compilation, linking, and usage of OpenGL shader programs.
         * It supports adding multiple shaders of different types, linking them into a program, and activating the program.
         */
        class Shader {
        public:
            /**
             * @brief Constructs a Shader object.
             *
             * Initializes the shader program.
             */
            Shader();

            /**
             * @brief Destructor that cleans up the shader program.
             *
             * Ensures that the shader program is properly deleted when the Shader instance goes out of scope.
             */
            ~Shader();

            /**
             * @brief Adds a shader of a specified type from a file.
             *
             * Compiles the shader source code from the provided file and attaches it to the shader program.
             *
             * @param shaderType The type of shader (e.g., GL_VERTEX_SHADER).
             * @param shaderFile The path to the shader source file.
             */
            void add_shader(GLenum shaderType, const std::string& shaderFile);

            /**
             * @brief Links and validates the shader program.
             *
             * Links all attached shader objects into a shader program and validates it.
             * Must be called after all shaders have been added.
             */
            void link_program();

            /**
             * @brief Activates the shader program.
             *
             * Makes the shader program the current program object.
             */
            void activate() const;

            /**
             * @brief Deletes the shader program.
             *
             * Deletes the shader program and resets the program ID.
             */
            void cleanup();

            /**
             * @brief Set the path to the shader folder
             *
             * @param path Specifies the path to the folder
             */
            void set_path(const std::string& path);

            /**
             * @brief Gets the shader program ID.
             *
             * @return The OpenGL shader program ID.
             */
            [[nodiscard]] GLuint get_ID() const noexcept;

            /**
             * @brief Adds a uniform location to the uniform location map.
             *
             * @param name The name of the uniform variable.
             */
            void add_uniform_location(const std::string& name);

            /**
             * @brief Sets a uniform variable in the shader program.
             *
             * Overloaded methods for different types.
             */

             // Integer uniforms
            void set_uniform(const std::string& name, GLint v0);
            void set_uniform(const std::string& name, GLint v0, GLint v1);
            void set_uniform(const std::string& name, GLint v0, GLint v1, GLint v2);
            void set_uniform(const std::string& name, GLint v0, GLint v1, GLint v2, GLint v3);
            void set_uniform(const std::string& name, GLsizei count, const GLint* value);

            // Unsigned integer uniforms
            void set_uniform(const std::string& name, GLuint v0);
            void set_uniform(const std::string& name, GLuint v0, GLuint v1);
            void set_uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2);
            void set_uniform(const std::string& name, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
            void set_uniform(const std::string& name, GLsizei count, const GLuint* value);

            // Float uniforms
            void set_uniform(const std::string& name, GLfloat v0);
            void set_uniform(const std::string& name, GLfloat v0, GLfloat v1);
            void set_uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2);
            void set_uniform(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
            void set_uniform(const std::string& name, GLsizei count, const GLfloat* value);

            // Matrix uniforms
            void set_uniform_matrix(const std::string& name, const GLfloat* value, GLsizei count, GLboolean transpose, GLenum matrixType);

            /**
			 * @brief Binds a uniform block to a binding point.
			 *
			 * @param blockName The name of the uniform block in the shader.
			 * @param bindingPoint The binding point to associate with the uniform block.
			 */
            void bind_uniform_block(const std::string& blockName, GLuint bindingPoint);

            // Equality operator.
            bool operator==(const Shader& other) const noexcept;

            // Inequality operator.
            bool operator!=(const Shader& other) const noexcept;

        private:

            /**
             * @brief Reads the contents of a file into a string.
             *
             * @param filename The path to the file.
             * @return The contents of the file as a string.
             */
            std::string get_file_contents(const std::string& filename) const;

            /**
             * @brief Retrieves the uniform location from the map.
             *
             * @param name The name of the uniform variable.
             * @return The location of the uniform variable.
             */
            GLint get_uniform_location(const std::string& name) const;

        private:

            GLuint ID_ = 0;                             ///< OpenGL shader program ID.
            std::vector<GLuint> shaders_;               ///< Container for shader object IDs.
            std::string path_ = "resources/shaders/";   ///< Path to the shader folder.
            std::unordered_map<std::string, GLint> uniform_locations_; ///< Map of uniform names to locations.

        };

    } // namespace Graphics

} // namespace Gem
