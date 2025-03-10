#include <Gem/Graphics/textures/tex_3D.h>

namespace Gem {

	namespace Graphics {

		// Constructor
		Texture3D::Texture3D() {
			init();
		}

		// Destructor
		Texture3D::~Texture3D() {
			// Base class destructor handles texture deletion
		}

		// Initialize the texture
		void Texture3D::init() {
			generate();

			bind(0); // Default binding to texture unit 0 for initialization

			// Set default texture parameters
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);

			unbind();

			is_initialized_ = true;
		}

		// Generate the texture
		void Texture3D::generate() {
			Texture::generate();
			// Additional generation logic if needed
		}

		// Bind the texture
		void Texture3D::bind(GLuint texture_unit) const {
			GL::active_texture(GL_TEXTURE0 + texture_unit);
			GL::bind_texture(GL_TEXTURE_3D, texture_ID_);
		}

		// Unbind the texture
		void Texture3D::unbind() const {
			GL::bind_texture(GL_TEXTURE_3D, 0);
		}

		// Generate mipmaps
		void Texture3D::generate_mipmaps() const {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture3D::generate_mipmaps: Texture not initialized." << std::endl;
				throw std::runtime_error("Texture not initialized.");
			}
			bind(0); // Bind to any texture unit, here 0
			GL::generate_mipmap(GL_TEXTURE_3D);
			unbind();
		}

		// Load a 3D texture from a set of image files
		void Texture3D::load_texture(const std::vector<std::string>& texture_names) {
			if (!is_initialized_) {
				std::cerr << "ERROR::Texture3D::load_texture: Texture not initialized. Call init() first." << std::endl;
				throw std::runtime_error("Texture not initialized.");
			}

			if (texture_names.empty()) {
				std::cerr << "ERROR::Texture3D::load_texture: No texture names provided." << std::endl;
				return;
			}

			std::vector<unsigned char*> texture_data_list;
			int width = 0, height = 0, channels = 0;

			// Load all texture images
			for (const auto& texture_name : texture_names) {
				std::string full_filename = path_ + texture_name;

				stbi_set_flip_vertically_on_load(true); // Flip the image vertically if needed
				unsigned char* texture_data = stbi_load(full_filename.c_str(), &width, &height, &channels, STBI_rgb_alpha);

				if (!texture_data) {
					std::cerr << "ERROR::Texture3D::load_texture: Failed to load texture '" << full_filename << "'.\nTry to change the path with set_path() to your local texture folder." << std::endl;
					// Free previously loaded images
					for (auto data : texture_data_list) {
						stbi_image_free(data);
					}
					return;
				}

				// Store dimensions from the first image
				if (texture_data_list.empty()) {
					width_ = static_cast<GLuint>(width);
					height_ = static_cast<GLuint>(height);
				}
				else {
					if (width != static_cast<int>(width_) || height != static_cast<int>(height_)) {
						std::cerr << "ERROR::Texture3D::load_texture: Texture '" << full_filename << "' has different dimensions than previous textures." << std::endl;
						stbi_image_free(texture_data);
						// Free previously loaded images
						for (auto data : texture_data_list) {
							stbi_image_free(data);
						}
						return;
					}
				}

				texture_data_list.push_back(texture_data);
			}

			depth_ = static_cast<GLuint>(texture_data_list.size());

			// Allocate storage for the 3D texture
			bind(0);
			GL::tex_storage_3d(GL_TEXTURE_3D, 1, GL_RGBA8, width_, height_, depth_);

			// Upload texture data for each layer
			for (GLuint i = 0; i < depth_; ++i) {
				GL::tex_sub_image_3d(GL_TEXTURE_3D, 0, 0, 0, i, width_, height_, 1, GL_RGBA, GL_UNSIGNED_BYTE, texture_data_list[i]);
			}

			unbind();

			// Free the loaded texture data
			for (auto data : texture_data_list) {
				stbi_image_free(data);
			}
		}

		// Set the min filter parameter
		void Texture3D::set_min_filter(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, param);
			unbind();
		}

		// Set the mag filter parameter
		void Texture3D::set_mag_filter(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, param);
			unbind();
		}

		// Set the wrap parameter
		void Texture3D::set_wrap(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, param);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, param);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, param);
			unbind();
		}

		// Set the wrap S parameter
		void Texture3D::set_wrap_s(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, param);
			unbind();
		}

		// Set the wrap T parameter
		void Texture3D::set_wrap_t(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, param);
			unbind();
		}

		// Set the wrap R parameter
		void Texture3D::set_wrap_r(GLint param) {
			bind(0);
			GL::tex_parameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, param);
			unbind();
		}

		// Get the width of the texture
		[[nodiscard]] GLuint Texture3D::get_width() const noexcept {
			return width_;
		}

		// Get the height of the texture
		[[nodiscard]] GLuint Texture3D::get_height() const noexcept {
			return height_;
		}

		// Get the depth of the texture
		[[nodiscard]] GLuint Texture3D::get_depth() const noexcept {
			return depth_;
		}

		// Equality operator
		bool Texture3D::operator==(const Texture3D& other) const noexcept {
			return texture_ID_ == other.texture_ID_;
		}

		// Inequality operator
		bool Texture3D::operator!=(const Texture3D& other) const noexcept {
			return !(*this == other);
		}

	} // namespace Graphics

} // namespace Gem
