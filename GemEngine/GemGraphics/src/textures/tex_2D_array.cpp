#include <Gem/Graphics/textures/tex_2D_array.h>

namespace Gem {

	namespace Graphics {

		// Constructor
		Texture2DArray::Texture2DArray(GLuint width, GLuint height, GLuint max_layers)
			: width_(width), height_(height), max_layers_(max_layers) {
			init();
		}

		// Destructor
		Texture2DArray::~Texture2DArray() {
			// Base class destructor handles texture deletion
		}

		// Initialize the texture array
		void Texture2DArray::init() {
			generate();

			bind(0); // Bind to texture unit 0 for initialization

			// Allocate storage for the texture array
			GL::tex_storage_3d(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width_, height_, max_layers_);
			is_storage_allocated_ = true;

			// Set default texture parameters
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

			unbind();

			is_initialized_ = true;
		}

		// Generate the texture array
		void Texture2DArray::generate() {
			Texture::generate();
			// Additional generation logic if needed
		}

		// Bind the texture array
		void Texture2DArray::bind(GLuint texture_unit) const {
			GL::active_texture(GL_TEXTURE0 + texture_unit);
			GL::bind_texture(GL_TEXTURE_2D_ARRAY, texture_ID_);
		}

		// Unbind the texture array
		void Texture2DArray::unbind() const {
			GL::bind_texture(GL_TEXTURE_2D_ARRAY, 0);
		}

		// Generate mipmaps
		void Texture2DArray::generate_mipmaps() const {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture2DArray::generate_mipmaps: Texture array not initialized." << std::endl;
				throw std::runtime_error("Texture array not initialized.");
			}
			bind(0); // Bind to any texture unit, here 0
			GL::generate_mipmap(GL_TEXTURE_2D_ARRAY);
			unbind();
		}

		// Add a texture to the array
		void Texture2DArray::add_texture(const std::string& texture_name) {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture2DArray::add_texture: Texture array not initialized. Call init() first." << std::endl;
				throw std::runtime_error("Texture array not initialized.");
			}

			if (!is_storage_allocated_) {
				std::cerr << "ERROR::Texture2DArray::add_texture: Storage not allocated for texture array." << std::endl;
				throw std::runtime_error("Texture array storage not allocated.");
			}

			if (layer_count_ >= max_layers_) {
				std::cerr << "ERROR::Texture2DArray::add_texture: Maximum number of textures reached." << std::endl;
				return;
			}

			// Load the texture image
			int width, height, channels;
			std::string full_filename = path_ + texture_name;

			stbi_set_flip_vertically_on_load(true); // Flip the image vertically if needed
			unsigned char* texture_data = stbi_load(full_filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

			if (!texture_data) {
				std::cerr << "ERROR::Texture2DArray::add_texture: Failed to load texture '" << full_filename << "'.\nTry to change the path with set_path() to your local texture folder." << std::endl;
				return;
			}

			if (static_cast<GLuint>(width) != width_ || static_cast<GLuint>(height) != height_) {
				std::cerr << "ERROR::Texture2DArray::add_texture: Texture dimensions do not match the array dimensions." << std::endl;
				stbi_image_free(texture_data);
				return;
			}

			// Upload the texture data to the GPU
			bind(0); // Bind to any texture unit, here 0
			GL::tex_sub_image_3d(GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer_count_, width_, height_, 1, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
			unbind();

			// Free the loaded texture data
			stbi_image_free(texture_data);

			++layer_count_;
		}

		// Set the min filter parameter
		void Texture2DArray::set_min_filter(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, param);
			unbind();
		}

		// Set the mag filter parameter
		void Texture2DArray::set_mag_filter(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, param);
			unbind();
		}

		// Set the wrap parameter
		void Texture2DArray::set_wrap(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, param);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, param);
			unbind();
		}

		// Set the wrap S parameter
		void Texture2DArray::set_wrap_s(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, param);
			unbind();
		}

		// Set the wrap T parameter
		void Texture2DArray::set_wrap_t(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, param);
			unbind();
		}

		// Get the width of the textures
		[[nodiscard]] GLuint Texture2DArray::get_width() const noexcept {
			return width_;
		}

		// Get the height of the textures
		[[nodiscard]] GLuint Texture2DArray::get_height() const noexcept {
			return height_;
		}

		// Get the number of layers
		[[nodiscard]] GLuint Texture2DArray::get_layer_count() const noexcept {
			return layer_count_;
		}

		// Equality operator
		bool Texture2DArray::operator==(const Texture2DArray& other) const noexcept {
			return texture_ID_ == other.texture_ID_;
		}

		// Inequality operator
		bool Texture2DArray::operator!=(const Texture2DArray& other) const noexcept {
			return !(*this == other);
		}

	} // namespace Graphics

} // namespace Gem
