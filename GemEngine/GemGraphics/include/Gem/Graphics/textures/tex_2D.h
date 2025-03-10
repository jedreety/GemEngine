#pragma once

#include <Gem/Graphics/textures/texture.h>
#include <stb_image.h>

namespace Gem {

    namespace Graphics {

        /**
         * @brief Texture2D class for managing a 2D texture in OpenGL.
         *
         * The Texture2D class encapsulates the creation, binding, and management of a single 2D texture.
         * It allows loading a texture from an image file and setting texture parameters.
         */
        class Texture2D : public Texture {

        public:
            /**
             * @brief Constructs a Texture2D object.
             */
            Texture2D();

            /**
             * @brief Destructor that cleans up the texture.
             */
            ~Texture2D();

            /**
             * @brief Initializes the texture.
             */
            void init() override;

            /**
             * @brief Binds the texture to the specified texture unit.
             *
             * @param texture_unit The texture unit index (e.g., 0 for GL_TEXTURE0).
             */
            void bind(GLuint texture_unit) const override;

            /**
             * @brief Unbinds the texture.
             */
            void unbind() const override;

            /**
             * @brief Generates mipmaps for the texture.
             */
            void generate_mipmaps() const override;

            /**
             * @brief Loads a texture from an image file.
             *
             * @param texture_name The name of the texture file (with extension).
             */
            void load_texture(const std::string& texture_name);

            /**
             * @brief Sets texture Min Filter.
             *
             * @param param The minification filter mode (e.g., GL_NEAREST, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR).
             */
            void set_min_filter(GLint param) override;

            /**
             * @brief Sets texture Mag Filter.
             *
             * @param param The magnification filter mode (e.g., GL_NEAREST, GL_LINEAR).
             */
            void set_mag_filter(GLint param) override;

            /**
             * @brief Sets Wrap Parameter for both S and T.
             *
             * @param param The wrapping mode (e.g., GL_REPEAT, GL_CLAMP_TO_EDGE).
             */
            void set_wrap(GLint param) override;

            /**
             * @brief Sets Wrap Parameter for S coordinate.
             *
             * @param param The wrapping mode.
             */
            void set_wrap_s(GLint param) override;

            /**
             * @brief Sets Wrap Parameter for T coordinate.
             *
             * @param param The wrapping mode.
             */
            void set_wrap_t(GLint param) override;

            /**
             * @brief Gets the width of the texture.
             *
             * @return The texture width.
             */
            [[nodiscard]] GLuint get_width() const noexcept;

            /**
             * @brief Gets the height of the texture.
             *
             * @return The texture height.
             */
            [[nodiscard]] GLuint get_height() const noexcept;

            /**
             * @brief Equality operator.
             *
             * Compares two Texture2D objects based on their texture IDs.
             *
             * @param other The other Texture2D object to compare with.
             * @return True if both have the same texture ID, false otherwise.
             */
            bool operator==(const Texture2D& other) const noexcept;

            /**
             * @brief Inequality operator.
             *
             * Compares two Texture2D objects based on their texture IDs.
             *
             * @param other The other Texture2D object to compare with.
             * @return True if they have different texture IDs, false otherwise.
             */
            bool operator!=(const Texture2D& other) const noexcept;

        private:

            /**
             * @brief Generates the texture.
             */
            void generate() override;

        private:

            GLuint width_ = 0;  ///< Width of the texture.
            GLuint height_ = 0; ///< Height of the texture.

        };

    } // namespace Graphics

} // namespace Gem
