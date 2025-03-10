#pragma once

#include <iostream>
#include <../../GemCore/include-protected/function_overload.h>


#include <Gem/Graphics/buffer.h>

namespace Gem {
    namespace Graphics {

        /**
         * @brief OpenGL VAO (Vertex Array Object) class for managing vertex array objects.
         *
         * The VAO class encapsulates an OpenGL VAO, providing methods to generate, bind, unbind,
         * link vertex attributes, and clean up the VAO. It simplifies VAO management within a graphics engine.
         */
        class VAO {
        public:
            /**
             * @brief Constructs a VAO object.
             */
            VAO() noexcept;

            /**
             * @brief Destructor that cleans up the VAO.
             *
             * Ensures that the VAO is properly deleted when the VAO instance goes out of scope.
             */
            ~VAO();

            /**
             * @brief Generates the VAO.
             *
             * Calls glGenVertexArrays to create a new OpenGL VAO.
             * Must be called before binding or linking attributes.
             */
            void generate();

            /**
             * @brief Binds the VAO.
             *
             * Calls glBindVertexArray to bind the VAO.
             * The VAO must be generated before calling this method.
             */
            void bind() const;

            /**
             * @brief Unbinds the VAO.
             *
             * Unbinds the VAO by binding to 0.
             */
            void unbind() const;

            /**
             * @brief Links a VBO to the VAO using a specified layout.
             *
             * Sets up the vertex attribute pointers and enables the vertex attribute array.
             * The VBO must be bound before calling this method.
             *
             * @param VBO The VBO to link.
             * @param layout The layout location of the attribute.
             * @param numComponents The number of components per vertex attribute.
             * @param type The data type of each component (e.g., GL_FLOAT).
             * @param stride The byte offset between consecutive vertex attributes.
             * @param offset The offset of the first component of the first attribute.
             * @param normalized Specifies whether fixed-point data values should be normalized.
             */
            void link_attrib(const Buffer& VBO, GLuint layout, GLint numComponents, GLenum type, GLsizei stride, const void* offset, GLboolean normalized = GL_FALSE);

            /**
             * @brief Deletes the VAO.
             *
             * Calls glDeleteVertexArrays to delete the VAO.
             * After calling this method, the VAO instance can no longer be used unless generate() is called again.
             */
            void cleanup();

            /**
             * @brief Gets the VAO ID.
             *
             * @return The OpenGL VAO ID.
             */
            [[nodiscard]] GLuint get_ID() const noexcept;

            /**
             * @brief Equality operator.
             *
             * Compares two VAO objects based on their IDs.
             *
             * @param other The other VAO object to compare with.
             * @return True if both VAOs have the same ID, false otherwise.
             */
            bool operator==(const VAO& other) const noexcept;

            /**
             * @brief Inequality operator.
             *
             * Compares two VAO objects based on their IDs.
             *
             * @param other The other VAO object to compare with.
             * @return True if the VAOs have different IDs, false otherwise.
             */
            bool operator!=(const VAO& other) const noexcept;

        private:
            GLuint ID_ = 0;             ///< OpenGL VAO ID.
            bool is_generated_ = false; ///< Flag indicating if the VAO has been generated.
        };

    } // namespace GL
} // namespace Gem
