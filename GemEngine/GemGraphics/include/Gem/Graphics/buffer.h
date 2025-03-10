#pragma once

#include <../../GemCore/include-protected/function_overload.h>
#include <iostream>

namespace Gem {
    namespace Graphics {

        /**
         * @brief OpenGL Buffer class for managing buffer objects.
         *
         * The Buffer class encapsulates an OpenGL buffer object, providing methods to generate, bind, unbind,
         * upload data, and clean up the buffer. It is designed to be flexible and easy to use within a graphics engine.
         */
        class Buffer {
        public:
            /**
             * @brief Constructs a Buffer object with an optional buffer type.
             *
             * @param type The OpenGL buffer type (e.g., GL_ARRAY_BUFFER). Defaults to GL_ARRAY_BUFFER.
             */
            Buffer(GLenum type = GL_ARRAY_BUFFER) noexcept;

            /**
             * @brief Destructor that cleans up the buffer.
             *
             * Ensures that the buffer object is properly deleted when the Buffer instance goes out of scope.
             */
            ~Buffer();

            /**
             * @brief Generates the buffer object.
             *
             * Calls glGenBuffers to create a new OpenGL buffer object.
             * Must be called before binding or setting data.
             */
            void generate();

            /**
             * @brief Binds the buffer.
             *
             * Calls glBindBuffer to bind the buffer object to its target.
             * Buffer must be generated before calling this method.
             */
            void bind() const;

            /**
             * @brief Unbinds the buffer.
             *
             * Unbinds the buffer from its target by binding to 0.
             */
            void unbind() const;

            /**
             * @brief Uploads data to the buffer.
             *
             * Calls glBufferData to create and initialize the buffer object's data store.
             * The buffer must be generated before calling this method.
             *
             * @param size The size in bytes of the data to be uploaded.
             * @param data A pointer to the data to be uploaded.
             * @param usage The expected usage pattern of the data store (e.g., GL_STATIC_DRAW).
             */
            void set_data(GLsizeiptr size, const void* data, GLenum usage);

            /**
             * @brief Deletes the buffer object.
             *
             * Calls glDeleteBuffers to delete the buffer object. After calling this method,
             * the Buffer instance can no longer be used unless generate() is called again.
             */
            void cleanup();

            /**
             * @brief Gets the buffer ID.
             *
             * @return The OpenGL buffer ID.
             */
            [[nodiscard]] GLuint get_ID() const noexcept;

            /**
             * @brief Gets the buffer type.
             *
             * @return The OpenGL buffer type (e.g., GL_ARRAY_BUFFER).
             */
            [[nodiscard]] GLenum get_type() const noexcept;

            /**
             * @brief Sets the buffer type before generation.
             *
             * Allows changing the buffer type if the buffer has not been generated yet.
             *
             * @param type The new buffer type to set.
             */
            void set_type(GLenum type);

            /**
             * @brief Equality operator.
             *
             * Compares two Buffer objects based on their IDs and types.
             *
             * @param other The other Buffer object to compare with.
             * @return True if both buffers have the same ID and type, false otherwise.
             */
            bool operator==(const Buffer& other) const noexcept;

            /**
             * @brief Inequality operator.
             *
             * Compares two Buffer objects based on their IDs and types.
             *
             * @param other The other Buffer object to compare with.
             * @return True if the buffers have different IDs or types, false otherwise.
             */
            bool operator!=(const Buffer& other) const noexcept;

        private:
            GLuint ID_ = 0;              ///< OpenGL buffer ID.
            GLenum type_;                ///< OpenGL buffer type (e.g., GL_ARRAY_BUFFER).
            bool is_generated_ = false;  ///< Flag indicating if the buffer has been generated.
        };

    } // namespace GL
} // namespace Gem
