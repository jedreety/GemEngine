#pragma once

#include <../../GemCore/include-protected/function_overload.h>
#include <cstdint>
#include <string>
#include <iostream>

namespace Gem {

    namespace Graphics {

        /**
         * @brief Base Texture class for managing common texture functionality in OpenGL.
         *
         * The Texture class encapsulates the common attributes and methods shared among different texture types.
         */
        class Texture {

        public:
            /**
             * @brief Virtual destructor to ensure proper cleanup in derived classes.
             */
            virtual ~Texture();

            /**
             * @brief Initializes the texture.
             *
             * Generates the texture and sets texture parameters.
             */
            virtual void init() = 0;

            /**
               * @brief Binds the texture to the specified texture unit.
               *
               * @param texture_unit The texture unit index (e.g., 0 for GL_TEXTURE0).
               */
            virtual void bind(GLuint texture_unit) const = 0;

            /**
             * @brief Unbinds the texture.
             */
            virtual void unbind() const = 0;

            /**
             * @brief Generates mipmaps for the texture.
             */
            virtual void generate_mipmaps() const = 0;

            /**
             * @brief Sets texture Min Filter.
             *
             * @param param The minification filter mode (e.g., GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR).
             */
            virtual void set_min_filter(GLint param) = 0;

            /**
             * @brief Sets texture Mag Filter.
             *
             * @param param The magnification filter mode (e.g., GL_NEAREST, GL_LINEAR).
             */
            virtual void set_mag_filter(GLint param) = 0;

            /**
             * @brief Sets Wrap Parameter.
             *
             * @param param The wrapping mode (e.g., GL_REPEAT, GL_CLAMP_TO_EDGE).
             */
            virtual void set_wrap(GLint param) = 0;

            /**
             * @brief Sets Wrap Parameter for S coordinate.
             *
             * @param param The wrapping mode.
             */
            virtual void set_wrap_s(GLint param) = 0;

            /**
             * @brief Sets Wrap Parameter for T coordinate.
             *
             * @param param The wrapping mode.
             */
            virtual void set_wrap_t(GLint param) = 0;

            /**
             * @brief Sets Wrap Parameter for R coordinate (if applicable).
             *
             * @param param The wrapping mode.
             */
            virtual void set_wrap_r(GLint param);

            /**
             * @brief Sets the path to the texture folder.
             *
             * @param path The path to the texture folder.
             */
            void set_path(const std::string& path);

            /**
             * @brief Gets the texture ID.
             *
             * @return The OpenGL texture ID.
             */
            [[nodiscard]] GLuint get_texture_ID() const noexcept;

        protected:

            /**
             * @brief Generates the texture.
             */
            virtual void generate();

        protected:

            GLuint texture_ID_ = 0;                     ///< OpenGL texture ID.
            bool is_initialized_ = false;               ///< Flag indicating if the texture has been initialized.
            std::string path_ = "resources/textures/";  ///< Path to the texture folder.

        };

    } // namespace Graphics

} // namespace Gem
