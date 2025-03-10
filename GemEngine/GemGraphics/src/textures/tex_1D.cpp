#include <Gem/Graphics/textures/tex_1D.h>

namespace Gem {

	namespace Graphics {

		// Constructor
		Texture1D::Texture1D() {
			init();
		}

		// Destructor
		Texture1D::~Texture1D() {
			// Base class destructor handles texture deletion
		}

		// Initialize the texture
		void Texture1D::init() {
			generate();

			bind(0); // Default binding to texture unit 0 for initialization

			// Set default texture parameters
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

			unbind();

			is_initialized_ = true;
		}

		// Generate the texture
		void Texture1D::generate() {
			Texture::generate();
			// Additional generation logic if needed
		}

		// Bind the texture
		void Texture1D::bind(GLuint texture_unit) const {
			GL::active_texture(GL_TEXTURE0 + texture_unit);
			GL::bind_texture(GL_TEXTURE_1D, texture_ID_);
		}

		// Unbind the texture
		void Texture1D::unbind() const {
			GL::bind_texture(GL_TEXTURE_1D, 0);
		}

		// Generate mipmaps
		void Texture1D::generate_mipmaps() const {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture1D::generate_mipmaps: Texture not initialized." << std::endl;
				throw std::runtime_error("Texture not initialized.");
			}
			bind(0); // Bind to any texture unit, here 0
			GL::generate_mipmap(GL_TEXTURE_1D);
			unbind();
		}

		// Load a texture from an image file
		void Texture1D::load_texture(const std::string& texture_name) {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture1D::load_texture: Texture not initialized. Call init() first." << std::endl;
				throw std::runtime_error("Texture not initialized.");
			}

			// Load the texture image
			int width, height, channels;
			std::string full_filename = path_ + texture_name;

			stbi_set_flip_vertically_on_load(false); // No need to flip for 1D textures
			unsigned char* texture_data = stbi_load(full_filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

			if (!texture_data) {
				std::cerr << "ERROR::Texture1D::load_texture: Failed to load texture '" << full_filename << "'.\nTry to change the path with set_path() to your local texture folder." << std::endl;
				return;
			}

			if (height != 1) {
				std::cerr << "ERROR::Texture1D::load_texture: Image height must be 1 for 1D textures." << std::endl;
				stbi_image_free(texture_data);
				return;
			}

			width_ = static_cast<GLuint>(width);

			// Upload the texture data to the GPU
			bind(0); // Bind to any texture unit, here 0
			GL::tex_image_1d(GL_TEXTURE_1D, 0, GL_RGBA8, width_, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
			unbind();

			// Free the loaded texture data
			stbi_image_free(texture_data);
		}

		// Set the min filter parameter
		void Texture1D::set_min_filter(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, param);
			unbind();
		}

		// Set the mag filter parameter
		void Texture1D::set_mag_filter(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, param);
			unbind();
		}

		// Set the wrap parameter
		void Texture1D::set_wrap(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, param);
			unbind();
		}

		// Set the wrap S parameter
		void Texture1D::set_wrap_s(GLint param) {
			bind(0); // Bind to any texture unit, here 0
			GL::tex_parameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, param);
			unbind();
		}

		// Get the width of the texture
		[[nodiscard]] GLuint Texture1D::get_width() const noexcept {
			return width_;
		}

		// Equality operator
		bool Texture1D::operator==(const Texture1D& other) const noexcept {
			return texture_ID_ == other.texture_ID_;
		}

		// Inequality operator
		bool Texture1D::operator!=(const Texture1D& other) const noexcept {
			return !(*this == other);
		}

	} // namespace Graphics

} // namespace Gem
