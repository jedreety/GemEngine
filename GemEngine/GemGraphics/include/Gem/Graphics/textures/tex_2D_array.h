#pragma once

#include <Gem/Graphics/textures/texture.h>
#include <stb_image.h>
#include <vector>

namespace Gem {

    namespace Graphics {

        /**
         * @brief Texture2DArray class for managing a 2D texture array in OpenGL.
         *
         * The Texture2DArray class encapsulates the creation, binding, and management of a 2D texture array.
         * It allows loading multiple textures into a single texture array.
         */
        class Texture2DArray : public Texture {

        public:
            /**
             * @brief Constructs a Texture2DArray object.
             *
             * @param width Width of each texture in the array.
             * @param height Height of each texture in the array.
             * @param max_layers Maximum number of layers (textures) in the array.
             */
            Texture2DArray(GLuint width, GLuint height, GLuint max_layers);

            /**
             * @brief Destructor that cleans up the texture.
             */
            ~Texture2DArray();

            /**
             * @brief Initializes the texture array.
             */
            void init() override;

            /**
             * @brief Binds the texture array to the specified texture unit.
             *
             * @param texture_unit The texture unit index (e.g., 0 for GL_TEXTURE0).
             */
            void bind(GLuint texture_unit) const override;

            /**
             * @brief Unbinds the texture array.
             */
            void unbind() const override;

            /**
             * @brief Generates mipmaps for the texture array.
             */
            void generate_mipmaps() const override;

            /**
             * @brief Adds a texture to the array from an image file.
             *
             * @param texture_name The name of the texture file (with extension).
             */
            void add_texture(const std::string& texture_name);

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
             * @brief Gets the width of the textures in the array.
             *
             * @return The texture width.
             */
            [[nodiscard]] GLuint get_width() const noexcept;

            /**
             * @brief Gets the height of the textures in the array.
             *
             * @return The texture height.
             */
            [[nodiscard]] GLuint get_height() const noexcept;

            /**
             * @brief Gets the number of layers currently in use.
             *
             * @return The number of layers.
             */
            [[nodiscard]] GLuint get_layer_count() const noexcept;

            /**
             * @brief Equality operator.
             *
             * Compares two Texture2DArray objects based on their texture IDs.
             *
             * @param other The other Texture2DArray object to compare with.
             * @return True if both have the same texture ID, false otherwise.
             */
            bool operator==(const Texture2DArray& other) const noexcept;

            /**
             * @brief Inequality operator.
             *
             * Compares two Texture2DArray objects based on their texture IDs.
             *
             * @param other The other Texture2DArray object to compare with.
             * @return True if they have different texture IDs, false otherwise.
             */
            bool operator!=(const Texture2DArray& other) const noexcept;

        private:

            /**
             * @brief Generates the texture array.
             */
            void generate() override;

        private:

            GLuint width_;               ///< Width of each texture in the array.
            GLuint height_;              ///< Height of each texture in the array.
            GLuint max_layers_;          ///< Maximum number of layers in the array.
            GLuint layer_count_ = 0;     ///< Current number of layers used.
            bool is_storage_allocated_ = false; ///< Flag indicating if storage has been allocated.

        };

    } // namespace Graphics

} // namespace Gem
