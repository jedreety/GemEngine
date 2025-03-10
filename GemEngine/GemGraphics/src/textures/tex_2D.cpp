#include <Gem/Graphics/textures/tex_2d.h>

namespace Gem {

	namespace Graphics {

		// Constructor
		Texture2D::Texture2D() {
			init();
		}

		// Destructor
		Texture2D::~Texture2D() {
			// Base class destructor handles texture deletion
		}

		// Initialize the texture
		void Texture2D::init() {
			generate();

			bind(0); // Default binding to texture unit 0 for initialization

			// Set default texture parameters
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			unbind();

			is_initialized_ = true;
		}

		// Generate the texture
		void Texture2D::generate() {
			Texture::generate();
			// Additional generation logic if needed
		}

		// Bind the texture
		void Texture2D::bind(GLuint texture_unit) const {
			GL::active_texture(GL_TEXTURE0 + texture_unit);
			GL::bind_texture(GL_TEXTURE_2D, texture_ID_);
		}

		// Unbind the texture
		void Texture2D::unbind() const {
			GL::bind_texture(GL_TEXTURE_2D, 0);
		}

		// Generate mipmaps
		void Texture2D::generate_mipmaps() const {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture2D::generate_mipmaps: Texture not initialized." << std::endl;
				throw std::runtime_error("Texture not initialized.");
			}
			bind(0); // Bind to any texture unit, here 0
			GL::generate_mipmap(GL_TEXTURE_2D);
			unbind();
		}

		// Load a texture from an image file
		void Texture2D::load_texture(const std::string& texture_name) {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture2D::load_texture: Texture not initialized. Call init() first." << std::endl;
				throw std::runtime_error("Texture not initialized.");
			}

			// Load the texture image
			int width, height, channels;
			std::string full_filename = path_ + texture_name;

			stbi_set_flip_vertically_on_load(true); // Flip the image vertically if needed
			unsigned char* texture_data = stbi_load(full_filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

			if (!texture_data) {
				std::cerr << "ERROR::Texture2D::load_texture: Failed to load texture '" << full_filename << "'.\nTry to change the path with set_path() to your local texture folder." << std::endl;
				return;
			}

			width_ = static_cast<GLuint>(width);
			height_ = static_cast<GLuint>(height);

			// Upload the texture data to the GPU
			bind(0); // Bind to any texture unit, here 0
			GL::tex_image_2d(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
			unbind();

			// Free the loaded texture data
			stbi_image_free(texture_data);
		}

		// Set the min filter parameter
		void Texture2D::set_min_filter(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, param);
			unbind();
		}

		// Set the mag filter parameter
		void Texture2D::set_mag_filter(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, param);
			unbind();
		}

		// Set the wrap parameter
		void Texture2D::set_wrap(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
			unbind();
		}

		// Set the wrap S parameter
		void Texture2D::set_wrap_s(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
			unbind();
		}

		// Set the wrap T parameter
		void Texture2D::set_wrap_t(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
			unbind();
		}

		// Get the width of the texture
		[[nodiscard]] GLuint Texture2D::get_width() const noexcept {
			return width_;
		}

		// Get the height of the texture
		[[nodiscard]] GLuint Texture2D::get_height() const noexcept {
			return height_;
		}

		// Equality operator
		bool Texture2D::operator==(const Texture2D& other) const noexcept {
			return texture_ID_ == other.texture_ID_;
		}

		// Inequality operator
		bool Texture2D::operator!=(const Texture2D& other) const noexcept {
			return !(*this == other);
		}

	} // namespace Graphics

} // namespace Gem
